# Plaits VA for KORG logue SDK v1

[English](#english) | [日本語](#日本語)

<a id="english"></a>

## English introduction

An experimental port of the Mutable Instruments Plaits virtual-analog engine
for KORG logue SDK v1 instruments. Ready-to-load builds are provided for the
Nu:Tekt NTS-1 mkI digital kit, minilogue xd, and prologue.

These are real-time custom oscillator units, not sample packs. The instrument
runs the synthesis engine through its KORG logue SDK oscillator slot.

## Download

Download the file for your instrument:

| Instrument | File |
| --- | --- |
| Nu:Tekt NTS-1 mkI digital kit | [`plaits_va_mki.ntkdigunit`](https://github.com/ksd6700/plaits_va_mki-NTS-1-digital-kit/raw/main/dist/plaits_va_mki.ntkdigunit) |
| minilogue xd | [`plaits_va_minilogue_xd.mnlgxdunit`](https://github.com/ksd6700/plaits_va_mki-NTS-1-digital-kit/raw/main/dist/plaits_va_minilogue_xd.mnlgxdunit) |
| prologue | [`plaits_va_prologue.prlgunit`](https://github.com/ksd6700/plaits_va_mki-NTS-1-digital-kit/raw/main/dist/plaits_va_prologue.prlgunit) |

Load the unit file with the matching KORG Librarian/logue utility for your
instrument.

Version `0.2-0` raises the output level compared with the first build.

SHA-256:

```text
11e69f3f26feeac09efe478d26970a164b23e8f0916f3615068afafc8a6c779a  dist/plaits_va_mki.ntkdigunit
58e94224c191890bdea4e1b68161e7967edd8c6945055bc5bf4070ceba8fce40  dist/plaits_va_minilogue_xd.mnlgxdunit
a9607c03981365b3e5e12e8862bbaaee51efa1708ab1341a7d6c2bfa83e60289  dist/plaits_va_prologue.prlgunit
```

## What Is This?

`VA-MKI`, `VA-XD`, and `VA-PRLG` are compact custom oscillators built from the
Mutable Instruments Plaits `VirtualAnalogEngine`.

It is not a complete Plaits clone. Plaits contains many synthesis models; this
project ports one practical first slice: the virtual-analog model based on two
continuously variable waveforms, detuning, and hard-sync-style variants.

The goal is to bring a focused piece of the Plaits sound world to KORG logue
SDK v1 instruments while keeping each unit small, buildable, and easy to test.

## Background

Mutable Instruments Plaits is a Eurorack macro-oscillator with 16 synthesis
models. The original Plaits design uses floating-point DSP code and emphasizes
band-limited synthesis at the base audio rate.

This project uses the Plaits virtual-analog engine, whose original model is
centered around:

- two detuned variable waveforms
- `TIMBRE` as a variable square/pulse/hard-sync control
- `MORPH` as a variable saw/triangle/notch control
- an `AUX` output carrying a related hard-sync variant

KORG's logue SDK allows compatible instruments to load custom oscillators and
effects. This project targets the custom oscillator path: the unit receives
pitch and parameter information from the host instrument and writes an audio
buffer back to its synth engine.

## Sound Character

Expect a digital virtual-analog voice rather than a plain saw or square wave.
The interesting part is how the controls slide between pulse width, saw shape,
notch width, oscillator detuning, and sync-like tones.

At gentle settings it can behave like a compact VA oscillator. Pushing `Shape`,
`Shift-Shape`, and `Harm` brings out thinner pulses, wider notches, interval
detuning, and brighter hard-sync edges. The `OutAux` parameter lets you blend
between the main Plaits OUT-style signal and the AUX-style variant.

## Controls

| Control | Internal Mapping | What It Does |
| --- | --- | --- |
| Shape | Plaits `timbre` | Variable square/pulse and sync-like brightness |
| Shift-Shape | Plaits `morph` | Variable saw/triangle/notch shape |
| Harm | Plaits `harmonics` | Detuning/spread between the two waves |
| OutAux | OUT/AUX crossfade | Blends the main and alternate engine outputs |
| Level | Output gain | Trims the oscillator level |
| Fine | Pitch trim | +/- 1 semitone tuning trim |

## Supported Builds

- NTS-1 mkI: `ports/plaits_va_mki`, platform `nutekt-digital`, display name `VA-MKI`
- minilogue xd: `ports/plaits_va_minilogue_xd`, platform `minilogue-xd`, display name `VA-XD`
- prologue: `ports/plaits_va_prologue`, platform `prologue`, display name `VA-PRLG`
- Unit type: `osc`
- Mutable source: Plaits `VirtualAnalogEngine`

NTS-1 mkII, microKORG2, drumlogue, and NTS-3 use newer/different logue SDK unit
APIs and are not included in this v1 build set.

## Build From Source

The repository includes the ready-to-load file in `dist/`, so building is only
needed if you want to modify the source.

External source trees are expected locally:

- `external/logue-sdk`: KORG logue SDK
- `external/eurorack`: Mutable Instruments eurorack source with submodules

Build steps:

```sh
cd ports/plaits_va_mki
make
make install
```

Replace `ports/plaits_va_mki` with `ports/plaits_va_minilogue_xd` or
`ports/plaits_va_prologue` to build the other v1 targets.

The generated files are:

```text
ports/plaits_va_mki/plaits_va_mki.ntkdigunit
ports/plaits_va_minilogue_xd/plaits_va_minilogue_xd.mnlgxdunit
ports/plaits_va_prologue/plaits_va_prologue.prlgunit
```

## Notes And Limits

- This is experimental and unofficial.
- This is not a full Plaits port.
- Other Plaits engines, such as FM, wavetable, speech, strings, modal, and
  drums, are not included.
- The NTS-1 mkI oscillator environment is smaller and more constrained than the
  original Plaits hardware, so this project starts with one lightweight model.
- Output level was boosted in `0.2-0`; if it clips in a specific patch, lower
  the `Level` parameter.
- Back up your instrument's custom unit slots before loading experimental units.

## License And Naming

Mutable Instruments' STM32 firmware code is MIT licensed. KORG logue SDK
templates are BSD-3-Clause licensed.

The units are named `VA-MKI`, `VA-XD`, and `VA-PRLG` rather than using the
original product name. This is intentional: it keeps the project clearly marked
as an unofficial derivative experiment, not an official Mutable Instruments or
KORG release.

## References

- [Mutable Instruments Plaits documentation](https://pichenettes.github.io/mutable-instruments-documentation/modules/plaits/)
- [Mutable Instruments eurorack source](https://github.com/pichenettes/eurorack)
- [KORG logue SDK](https://korginc.github.io/logue-sdk/)
- [KORG logue-sdk repository](https://github.com/korginc/logue-sdk)

---

# 日本語

これは KORG logue SDK v1 対応機種向けの、実験的な Mutable Instruments DSP
移植プロジェクトです。Nu:Tekt NTS-1 mkI digital kit、minilogue xd、prologue
向けのビルドを配布しています。

サンプル音源ではなく、対応機種の中でリアルタイムに発音するカスタム・
オシレーターです。KORG logue SDK の oscillator unit として読み込みます。

## ダウンロード

使う機種に合わせてファイルをダウンロードしてください。

| 機種 | ファイル |
| --- | --- |
| Nu:Tekt NTS-1 mkI digital kit | [`plaits_va_mki.ntkdigunit`](https://github.com/ksd6700/plaits_va_mki-NTS-1-digital-kit/raw/main/dist/plaits_va_mki.ntkdigunit) |
| minilogue xd | [`plaits_va_minilogue_xd.mnlgxdunit`](https://github.com/ksd6700/plaits_va_mki-NTS-1-digital-kit/raw/main/dist/plaits_va_minilogue_xd.mnlgxdunit) |
| prologue | [`plaits_va_prologue.prlgunit`](https://github.com/ksd6700/plaits_va_mki-NTS-1-digital-kit/raw/main/dist/plaits_va_prologue.prlgunit) |

ダウンロードした unit ファイルを、各機種に対応した KORG Librarian / logue 系
ツールで読み込んでください。

`0.2-0` では、最初のビルドより出力レベルを上げています。

## これは何？

`VA-MKI`、`VA-XD`、`VA-PRLG` は、Mutable Instruments Plaits の
`VirtualAnalogEngine` を各機種向けに小さく包んだカスタム・オシレーターです。

Plaits 全体の完全移植ではありません。Plaits には多数のシンセシスモデルが
ありますが、このプロジェクトでは最初の実用的な一歩として、2つの可変波形、
デチューン、ハードシンク風の派生出力を持つ virtual analog モデルだけを
移植しています。

## 背景

Mutable Instruments Plaits は Eurorack のマクロ・オシレーターです。16種類の
シンセシスモデルを持ち、浮動小数点 DSP とバンドリミットされた合成を重視した
設計になっています。

今回使っている virtual analog モデルは、ざっくり言うと次のような音作りです。

- 2つのデチューン可能な可変波形
- `TIMBRE`: 可変スクエア/パルス/ハードシンク風の明るさ
- `MORPH`: 三角波からノッチ付きソーへ変化する可変ソー
- `AUX`: メイン出力とは違うハードシンク風の派生出力

一方、NTS-1 mkI は KORG logue SDK によって custom oscillator を読み込めます。
このユニットは NTS-1 からピッチとパラメータを受け取り、音声バッファに波形を
書き戻すことで発音します。フィルター、EG、FX などは NTS-1 側のキャラクターが
乗ります。

## 音のキャラクター

素の鋸波や矩形波というより、デジタルらしい virtual analog の音です。細い
パルス、ノッチの広いソー、2オシレーターのデチューン、ハードシンク風の鋭さが
連続的に変化します。

穏やかな設定では小さな VA オシレーターとして使えます。`Shape`、
`Shift-Shape`、`Harm` を動かしていくと、細いパルス、明るいノッチ、音程間隔の
あるデチューン、シンク系のエッジが出てきます。`OutAux` は Plaits の OUT 的な
信号と AUX 的な派生信号をクロスフェードするためのパラメータです。

## 操作

| 操作 | 内部の割り当て | 内容 |
| --- | --- | --- |
| Shape | Plaits `timbre` | 可変スクエア/パルス、シンク風の明るさ |
| Shift-Shape | Plaits `morph` | 可変ソー/三角波/ノッチの形 |
| Harm | Plaits `harmonics` | 2つの波形のデチューン/広がり |
| OutAux | OUT/AUX クロスフェード | メイン出力と派生出力を混ぜる |
| Level | 出力ゲイン | 音量調整 |
| Fine | ピッチ微調整 | +/- 1 semitone のチューニング |

## 対応ビルド

- NTS-1 mkI: `ports/plaits_va_mki`, platform `nutekt-digital`, 表示名 `VA-MKI`
- minilogue xd: `ports/plaits_va_minilogue_xd`, platform `minilogue-xd`, 表示名 `VA-XD`
- prologue: `ports/plaits_va_prologue`, platform `prologue`, 表示名 `VA-PRLG`
- ユニット種別: `osc`
- Mutable 側の元ソース: Plaits `VirtualAnalogEngine`

NTS-1 mkII、microKORG2、drumlogue、NTS-3 は SDK の unit API 世代や構造が違うため、
この v1 系ビルドセットにはまだ含めていません。

## ソースからビルドする場合

すぐ試すだけなら `dist/` の `.ntkdigunit` を使えば大丈夫です。ソースを変更したい
場合だけビルドしてください。

ローカルには次の外部ソースが必要です。

- `external/logue-sdk`: KORG logue SDK
- `external/eurorack`: Mutable Instruments eurorack source with submodules

ビルド手順:

```sh
cd ports/plaits_va_mki
make
make install
```

`ports/plaits_va_mki` の部分を `ports/plaits_va_minilogue_xd` や
`ports/plaits_va_prologue` に置き換えると、他の v1 ターゲットをビルドできます。

生成されるファイル:

```text
ports/plaits_va_mki/plaits_va_mki.ntkdigunit
ports/plaits_va_minilogue_xd/plaits_va_minilogue_xd.mnlgxdunit
ports/plaits_va_prologue/plaits_va_prologue.prlgunit
```

## 注意点

- 実験的な非公式プロジェクトです。
- Plaits の完全移植ではありません。
- FM、wavetable、speech、strings、modal、drums などの他モデルは入っていません。
- NTS-1 mkI の oscillator 環境は元の Plaits ハードウェアより小さいため、まずは
  軽くて扱いやすい1モデルだけを移植しています。
- `0.2-0` で出力レベルを上げています。パッチによって歪む場合は `Level` を下げて
  ください。
- 実験的な unit を読み込む前に、NTS-1 の custom unit スロットをバックアップして
  おくと安心です。

## ライセンスと名前について

Mutable Instruments の STM32 ファームウェアコードは MIT ライセンスです。KORG
logue SDK のテンプレートは BSD-3-Clause ライセンスです。

ユニット名を元製品名ではなく `VA-MKI`、`VA-XD`、`VA-PRLG` にしているのは
意図的です。これは公式の Mutable Instruments / KORG リリースではなく、非公式の
派生実験であることを明確にするためです。
