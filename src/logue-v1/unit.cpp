// logue SDK v1 oscillator wrapper for a small Plaits-derived engine.
//
// Mutable Instruments DSP code is MIT licensed. KORG SDK template code is
// BSD-3-Clause. See this repository's README for source links and naming notes.

#include "userosc.h"

#include <algorithm>
#include <new>
#include <stdint.h>

#include "plaits/dsp/dsp.h"
#include "plaits/dsp/engine/engine.h"
#include "plaits/dsp/engine/virtual_analog_engine.h"
#include "stmlib/utils/buffer_allocator.h"

namespace {

constexpr size_t kAllocatorSize = 512;
constexpr float kMinLevel = 0.5f;
constexpr float kMaxLevel = 2.0f;

alignas(plaits::VirtualAnalogEngine) uint8_t engine_storage[sizeof(plaits::VirtualAnalogEngine)];
uint8_t allocator_memory[kAllocatorSize];

float out_buffer[plaits::kMaxBlockSize];
float aux_buffer[plaits::kMaxBlockSize];

struct State {
  plaits::EngineParameters params;
  float aux_mix;
  float level;
  float fine_semitones;
  bool initialized;
  bool note_gate;
  bool note_rising;
};

State state;

plaits::VirtualAnalogEngine* engine() {
  return reinterpret_cast<plaits::VirtualAnalogEngine*>(engine_storage);
}

float clamp01(float value) {
  return std::min(std::max(value, 0.0f), 1.0f);
}

float clamp1(float value) {
  return std::min(std::max(value, -1.0f), 1.0f);
}

float percent_to_float(uint16_t value) {
  return clamp01(static_cast<float>(value) * 0.01f);
}

float bipolar_percent_to_float(uint16_t value) {
  return (static_cast<int32_t>(value) - 100) * 0.01f;
}

float level_from_percent(uint16_t value) {
  return kMinLevel + percent_to_float(value) * (kMaxLevel - kMinLevel);
}

float pitch_to_midi_note(uint16_t pitch) {
  const float note = static_cast<float>(pitch >> 8);
  const float fine = static_cast<float>(pitch & 0xff) * (1.0f / 256.0f);
  return note + fine + state.fine_semitones;
}

void init_engine() {
  new (engine()) plaits::VirtualAnalogEngine;

  stmlib::BufferAllocator allocator(allocator_memory, sizeof(allocator_memory));
  engine()->Init(&allocator);
  engine()->Reset();

  state.params.trigger = plaits::TRIGGER_LOW;
  state.params.note = 60.0f;
  state.params.timbre = 0.5f;
  state.params.morph = 0.5f;
  state.params.harmonics = 0.5f;
  state.params.accent = 0.8f;
  state.aux_mix = 0.0f;
  state.level = kMaxLevel;
  state.fine_semitones = 0.0f;
  state.initialized = true;
  state.note_gate = false;
  state.note_rising = false;
}

void render_block(
    const user_osc_param_t* params,
    int32_t* yn,
    uint32_t frames) {
  plaits::EngineParameters p = state.params;
  p.note = pitch_to_midi_note(params->pitch);

  const float lfo = q31_to_f32(params->shape_lfo);
  p.timbre = clamp01(p.timbre + lfo * 0.25f);

  if (state.note_rising) {
    p.trigger = plaits::TRIGGER_RISING_EDGE | plaits::TRIGGER_HIGH;
    state.note_rising = false;
  } else {
    p.trigger = state.note_gate ? plaits::TRIGGER_HIGH : plaits::TRIGGER_LOW;
  }

  while (frames) {
    const size_t block_size = std::min<size_t>(frames, plaits::kMaxBlockSize);
    bool already_enveloped = false;
    engine()->Render(p, out_buffer, aux_buffer, block_size, &already_enveloped);

    for (size_t i = 0; i < block_size; ++i) {
      const float mixed = out_buffer[i] + (aux_buffer[i] - out_buffer[i]) * state.aux_mix;
      *yn++ = f32_to_q31(clamp1(mixed * state.level));
    }

    frames -= block_size;
  }
}

}  // namespace

void OSC_INIT(uint32_t platform, uint32_t api) {
  (void)platform;
  (void)api;
  init_engine();
}

void OSC_CYCLE(
    const user_osc_param_t* const params,
    int32_t* yn,
    const uint32_t frames) {
  if (!state.initialized) {
    init_engine();
  }
  render_block(params, yn, frames);
}

void OSC_NOTEON(const user_osc_param_t* const params) {
  (void)params;
  state.note_gate = true;
  state.note_rising = true;
}

void OSC_NOTEOFF(const user_osc_param_t* const params) {
  (void)params;
  state.note_gate = false;
}

void OSC_PARAM(uint16_t index, uint16_t value) {
  switch (index) {
    case k_user_osc_param_id1:
      state.params.harmonics = percent_to_float(value);
      break;

    case k_user_osc_param_id2:
      state.aux_mix = percent_to_float(value);
      break;

    case k_user_osc_param_id3:
      state.level = level_from_percent(value);
      break;

    case k_user_osc_param_id4:
      state.fine_semitones = bipolar_percent_to_float(value);
      break;

    case k_user_osc_param_shape:
      state.params.timbre = param_val_to_f32(value);
      break;

    case k_user_osc_param_shiftshape:
      state.params.morph = param_val_to_f32(value);
      break;

    default:
      break;
  }
}

void OSC_MUTE(const user_osc_param_t* const params) {
  (void)params;
  engine()->Reset();
}

void OSC_VALUE(uint16_t value) {
  (void)value;
}
