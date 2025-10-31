# LED点滅プログラム (Rust版)

このプロジェクトは、ESP32 Dev ModuleのGPIO5に接続されたLEDを点滅させるRustプログラムです。

## 概要

このプログラムは、Arduino版の`hello_led`プログラムと同等の機能をRustで実装したものです。GPIO5に接続されたLEDを500msごとにON/OFFし、シリアルモニタにステータスメッセージを出力します。

## 必要なハードウェア

- ESP32 Dev Module
- LED × 1
- 抵抗（220Ω程度）× 1
- ブレッドボード
- ジャンパーワイヤー

## 回路構成

```
ESP32 GPIO5 ----> LED(+) ----> 抵抗(220Ω) ----> GND
```

1. ESP32のGPIO5ピンにLEDのアノード（長い方の足、+側）を接続
2. LEDのカソード（短い方の足、-側）に抵抗を接続
3. 抵抗のもう一方の端をESP32のGNDに接続

## 環境構築

このプログラムをビルド・実行する前に、ESP32 Rust開発環境を構築する必要があります。
詳細な手順は、[親ディレクトリのREADME.md](../README.md)を参照してください。

### 必要なツール

- Rust (rustup経由でインストール)
- espup
- espflash
- ESP32用ツールチェーン

## ビルドと実行

### 1. プロジェクトディレクトリに移動

```bash
cd rust/led_blink
```

### 2. ESP32を接続

ESP32 Dev ModuleをUSBケーブルでPCに接続します。

### 3. ビルドとフラッシュ

```bash
cargo run --release
```

このコマンドは以下を自動的に実行します：
1. プログラムのビルド
2. ESP32へのフラッシュ
3. シリアルモニタの起動

### 4. 動作確認

プログラムが正常に動作すると、以下のような出力が表示されます：

```
Ready
LED ON
LED OFF
LED ON
LED OFF
...
```

同時に、接続したLEDが500msごとに点滅します。

## プログラムの説明

### main.rs

```rust
#![no_std]
#![no_main]
```

このプログラムは`no_std`環境で動作します。これは、標準ライブラリを使用せず、組み込みシステム向けの最小限のランタイムで動作することを意味します。

### 主要な機能

1. **GPIO設定**: GPIO5を出力モードに設定
2. **LED制御**: `set_high()`でLEDをON、`set_low()`でLEDをOFF
3. **遅延**: `delay.delay_millis(500)`で500ms待機
4. **ログ出力**: `info!()`マクロでシリアルモニタにメッセージを出力

### Arduino版との比較

| 機能 | Arduino | Rust |
|------|---------|------|
| GPIO設定 | `pinMode(gpioPin, OUTPUT)` | `Output::new(io.pins.gpio5, Level::Low)` |
| LED ON | `digitalWrite(gpioPin, HIGH)` | `led.set_high()` |
| LED OFF | `digitalWrite(gpioPin, LOW)` | `led.set_low()` |
| 遅延 | `delay(interval)` | `delay.delay_millis(500)` |
| シリアル出力 | `Serial.println("LED ON")` | `info!("LED ON")` |

## トラブルシューティング

### ビルドエラー

環境変数が正しく設定されているか確認：

```bash
source $HOME/export-esp.sh
```

### フラッシュエラー

シリアルポートを明示的に指定：

```bash
cargo run --release -- --port /dev/ttyUSB0
```

### 権限エラー

dialoutグループに追加されているか確認：

```bash
groups
```

`dialout`が表示されない場合は、以下を実行して再ログイン：

```bash
sudo usermod -a -G dialout $USER
```

## カスタマイズ

### 点滅間隔の変更

`delay.delay_millis(500)`の値を変更することで、点滅間隔を調整できます。

```rust
delay.delay_millis(1000);  // 1秒間隔
```

### GPIOピンの変更

GPIO5以外のピンを使用する場合は、以下の行を変更します：

```rust
let mut led = Output::new(io.pins.gpio5, Level::Low);
// 例: GPIO2を使用する場合
let mut led = Output::new(io.pins.gpio2, Level::Low);
```

## 参考資料

- [esp-hal Documentation](https://docs.esp-rs.org/esp-hal/)
- [The Rust on ESP Book](https://docs.esp-rs.org/book/)
- [Arduino版 hello_led](../../2.1/hello_led/hello_led.ino)

## ライセンス

MIT OR Apache-2.0
