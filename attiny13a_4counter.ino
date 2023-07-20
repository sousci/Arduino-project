/*
 * Attiny13Aを使った4進カウンターIC
 * 
 * [動作説明]
 * PB0の状態がLOW→HIGH（ポジティブエッジ）になったら
 * 4つの出力端子が順に1つずつHIGHになる
 * 
 * [配線]
 * 1(PB5):リセット…開放しておく
 * 2(PB3):出力端子…3番目のLEDを接続
 * 3(PB4):出力端子…4番目のLEDを接続
 * 4(GND):電源の(-)を接続
 * 5(PB0):入力端子…10kΩでプルダウンしSWでVCCに接続するとHIGHとなる(1カウント)
 * 6(PB1):出力端子…1番目のLEDを接続
 * 7(PB2):出力端子…2番目のLEDを接続
 * 8(VCC):電源の(+)を接続
 */

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PINB0
#define FIRST_LED_PIN PORTB1
#define LAST_LED_PIN PORTB4
#define DEBOUNCE_DELAY 10 // 10msのデバウンスディレイ

uint8_t currentLedPin = FIRST_LED_PIN;

void setup() {
  DDRB &= ~(1 << DDB0); // PB0を入力ピンとして設定
  PORTB |= (1 << PORTB0); // PB0の内部プルアップ抵抗を有効化

  DDRB |= ((1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4)); // PB1-4を出力ピンとして設定
  PORTB &= ~((1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4)); // PB1-4のLEDを初期的に全て消灯
}

void loop() {
  static uint8_t lastButtonState = 0; // 前回のボタンの状態を保存
  uint8_t buttonState = PINB & (1 << BUTTON_PIN); // 現在のボタンの状態を読み取り

  // ボタンの状態が前回と異なり、かつ、ボタンが押されている場合
  if ((buttonState != lastButtonState) && buttonState) {
    PORTB &= ~((1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4)); // 全てのLEDを消灯
    PORTB |= (1 << currentLedPin); // 現在のLEDを点灯

    // 次のLEDに移動または最初のLEDに戻る
    currentLedPin++;
    if (currentLedPin > LAST_LED_PIN) {
      currentLedPin = FIRST_LED_PIN;
    }

    _delay_ms(DEBOUNCE_DELAY); // デバウンスディレイ
  }

  lastButtonState = buttonState; // 現在のボタンの状態を保存
}
