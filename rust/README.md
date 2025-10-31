# ESP32 Rust開発環境構築ガイド

このガイドでは、Ubuntu環境でESP32 Dev ModuleにRustプログラムを書き込むための環境構築手順を説明します。

## 目次

1. [前提条件](#前提条件)
2. [Rustのインストール](#rustのインストール)
3. [ESP32用ツールチェーンのインストール](#esp32用ツールチェーンのインストール)
4. [開発ツールのインストール](#開発ツールのインストール)
5. [プロジェクトの生成](#プロジェクトの生成)
6. [プログラムのビルドと書き込み](#プログラムのビルドと書き込み)
7. [トラブルシューティング](#トラブルシューティング)

## 前提条件

- Ubuntu 20.04以降
- USBポート（ESP32との接続用）
- インターネット接続

## Rustのインストール

### 1. Rustupのインストール

Rustの公式インストーラーである`rustup`を使用してRustをインストールします。

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

インストール中に表示されるプロンプトでは、デフォルトのインストールオプション（1）を選択してください。

### 2. 環境変数の設定

インストール後、以下のコマンドで環境変数を読み込みます。

```bash
source $HOME/.cargo/env
```

または、新しいターミナルセッションを開始してください。

### 3. インストールの確認

```bash
rustc --version
cargo --version
```

バージョン情報が表示されれば、インストールは成功です。

## ESP32用ツールチェーンのインストール

ESP32はXtensaアーキテクチャを使用しているため、専用のツールチェーンが必要です。

### 1. 必要な依存パッケージのインストール

```bash
sudo apt-get update
sudo apt-get install -y git curl gcc build-essential pkg-config libudev-dev libtinfo5 libusb-1.0-0-dev
```

### 2. espupのインストール

`espup`は、ESP32開発に必要なツールチェーンを簡単にインストールするためのツールです。

```bash
cargo install espup --locked
```

### 3. ESP32ツールチェーンのインストール

```bash
espup install
```

このコマンドは以下をインストールします：
- Espressif Rustフォーク（Xtensaターゲット対応）
- RISC-Vターゲット用のstableツールチェーン
- XtensaターゲットをサポートするLLVMフォーク
- 最終バイナリをリンクするGCCツールチェーン

### 4. 環境変数の設定

インストール完了後、以下のコマンドで環境変数を設定します。

```bash
source $HOME/export-esp.sh
```

この設定を永続化するには、以下を`~/.bashrc`または`~/.zshrc`に追加します。

```bash
echo 'source $HOME/export-esp.sh' >> ~/.bashrc
source ~/.bashrc
```

## 開発ツールのインストール

### 1. espflashのインストール

`espflash`は、ESP32にプログラムを書き込むためのツールです。

```bash
cargo install espflash --locked
```

### 2. esp-generateのインストール

`esp-generate`は、ESP32用のRustプロジェクトを生成するためのツールです。

```bash
cargo install esp-generate --locked
```

### 3. シリアルポートへのアクセス権限設定

ESP32との通信には、シリアルポートへのアクセス権限が必要です。

```bash
sudo usermod -a -G dialout $USER
```

この変更を有効にするには、一度ログアウトして再度ログインするか、システムを再起動してください。

## プロジェクトの生成

### 1. 新規プロジェクトの作成

`esp-generate`を使用して、新しいプロジェクトを作成します。

```bash
esp-generate
```

対話的なUIが表示されるので、以下の設定を行います：

- **Chip**: `esp32`を選択
- **Project name**: プロジェクト名を入力（例：`led_blink`）
- **Enable alloc**: 必要に応じて選択
- **Enable WiFi**: 不要な場合は無効
- **Enable Bluetooth**: 不要な場合は無効
- **Logging**: `log`を有効化（推奨）
- **Panic handler**: `esp-backtrace`を選択（推奨）

設定が完了したら、`s`キーを押してプロジェクトを生成します。

### 2. プロジェクトディレクトリへの移動

```bash
cd led_blink
```

## プログラムのビルドと書き込み

### 1. ESP32の接続

ESP32 Dev ModuleをUSBケーブルでPCに接続します。

### 2. シリアルポートの確認

```bash
ls /dev/ttyUSB*
```

通常、`/dev/ttyUSB0`として認識されます。

### 3. プログラムのビルドと書き込み

```bash
cargo run --release
```

このコマンドは以下を実行します：
1. プログラムのビルド
2. ESP32へのフラッシュ
3. シリアルモニタの起動

### 4. シリアルポートの指定（必要な場合）

デフォルトのポートが異なる場合は、以下のように指定します。

```bash
cargo run --release -- --port /dev/ttyUSB0
```

## LED点滅プログラムの例

`led_blink`ディレクトリには、GPIO5に接続されたLEDを点滅させるサンプルプログラムが含まれています。

### 回路構成

- GPIO5にLEDのアノード（+）を接続
- LEDのカソード（-）に抵抗（220Ω程度）を接続
- 抵抗のもう一方の端をGNDに接続

### プログラムの動作

- LEDが500msごとにON/OFFを繰り返します
- シリアルモニタに"LED ON"と"LED OFF"のメッセージが表示されます

## トラブルシューティング

### シリアルポートが見つからない

```bash
ls -l /dev/ttyUSB*
```

デバイスが表示されない場合：
1. USBケーブルが正しく接続されているか確認
2. ESP32のドライバがインストールされているか確認
3. 別のUSBポートを試す

### 書き込みエラー

```bash
espflash board-info
```

このコマンドでESP32が正しく認識されているか確認します。

### 権限エラー

```bash
sudo chmod 666 /dev/ttyUSB0
```

または、dialoutグループに追加されているか確認：

```bash
groups
```

`dialout`が表示されない場合は、再ログインが必要です。

### ビルドエラー

環境変数が正しく設定されているか確認：

```bash
echo $LIBCLANG_PATH
echo $PATH | grep .espressif
```

設定されていない場合は、再度`source $HOME/export-esp.sh`を実行してください。

## 参考資料

- [The Rust on ESP Book](https://docs.esp-rs.org/book/)
- [esp-rs GitHub Organization](https://github.com/esp-rs)
- [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- [esp-hal Documentation](https://docs.esp-rs.org/esp-hal/)

## ライセンス

このプロジェクトは、リポジトリのルートにあるLICENSEファイルに従います。
