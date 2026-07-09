# plaits_va_mki | KORG NTS-1 digital kit

Mutable Instruments DSP porting experiment for the KORG NTS-1 mkI digital kit.

## Current Target

The first scaffold is:

- `ports/plaits_va_mki`
- KORG platform: `nutekt-digital`
- Unit type: `osc`
- Output package: `.ntkdigunit`
- Mutable source: Plaits `VirtualAnalogEngine`

This is a practical first slice rather than a full module clone. It avoids the
full Plaits `Voice`, which registers 24 engines and is likely too large for a
comfortable mkI oscillator unit.

## External Sources

- `external/logue-sdk`: KORG logue SDK
- `external/eurorack`: Mutable Instruments eurorack source with submodules

## Next Milestones

1. Install or locate the KORG-supported `arm-none-eabi` toolchain.
2. Initialize KORG SDK submodules for CMSIS.
3. Build `ports/plaits_va_mki` and check binary size against the 32 KB mkI
   oscillator linker region.
4. If it fits, test the `.ntkdigunit` on the NTS-1 with Librarian or logue-cli.
5. If it does not fit, remove features from the selected engine or hand-port a
   smaller oscillator core.
