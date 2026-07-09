# VA-MKI

Experimental NTS-1 mkI oscillator wrapper around the Mutable Instruments Plaits
`VirtualAnalogEngine`.

This is intentionally not a full Plaits port. The mkI oscillator slot is tight:
the linker script gives the oscillator 32 KB of SRAM/code space, and the KORG
API exposes six edit-menu parameters plus Shape and Shift-Shape. Starting with a
single engine keeps the port small enough to measure and iterate.

## Controls

- Shape: Plaits `timbre`
- Shift-Shape: Plaits `morph`
- Harm: Plaits `harmonics`
- OutAux: crossfades Plaits OUT and AUX
- Level: output gain
- Fine: +/- 1 semitone tuning trim

## Build

From this directory:

```sh
make
make install
```

The expected output is `plaits_va_mki.ntkdigunit`.

The project references:

- `../../external/logue-sdk` for the KORG NTS-1 mkI SDK
- `../../external/eurorack` for Mutable Instruments Plaits and stmlib sources

Run `git submodule update --init` inside `external/logue-sdk` before building so
the KORG CMSIS dependency exists. Install the KORG SDK GCC 5.4 toolchain under
`external/logue-sdk/tools/gcc/` or pass `GCC_BIN_PATH=/path/to/bin` to `make`.

## License And Naming

Mutable Instruments' STM32F code is MIT licensed. KORG logue SDK templates are
BSD-3-Clause licensed. Do not release this under the Mutable Instruments name or
the original Plaits product name; Mutable's repository explicitly asks
derivative works to avoid those names.
