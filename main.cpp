Для ATxmega128A1 возможны следующие прерывания по USART:

USART_RXC: Прерывание по приёму данных (Receive Complete). Вызывается когда USART принимает байт данных.
USART_TXC: Прерывание по передаче данных (Transmit Complete). Вызывается когда USART передаёт байт данных.
USART_DRE: Прерывание по готовности передачи данных (Data Register Empty). Вызывается когда регистр данных USART пуст и готов к передаче новых данных.
USART_FRAME_ERR: Прерывание по ошибке кадра (Frame Error). Вызывается когда USART обнаруживает ошибку кадра во время приёма данных.
USART_BUFOVF: Прерывание по переполнению буфера (Buffer Overflow). Вызывается когда буфер USART переполнен и новые данные не могут быть приняты.
Эти прерывания можно включить или выключить с помощью соответствующих битовых масок в регистрах USART.

Например, чтобы включить прерывание по приёму данных USART0, можно использовать следующий код:

c
CopyInsert
UCSR0B |= (1 << RXCIE0);
А чтобы выключить прерывание по передаче данных USART1, можно использовать следующий код:

c
CopyInsert
UCSR1B &= ~(1 << TXCIE1);
Где UCSR0B и UCSR1B - регистры управления USART0 и USART1 соответственно.



#include <avr/io.h>
#include <avr/interrupt.h>

// Обработчик прерываний USART0
ISR(USART0_RX_vect) {
  // Обработка прерывания по приёму данных USART0
  uint8_t data = UDR0;
  // Делаем что-то с данными
  PORTB ^= (1 << PB0); // Мигаем светодиодом
}

ISR(USART0_TX_vect) {
  // Обработка прерывания по передаче данных USART0
  // Делаем что-то после передачи данных
  PORTB ^= (1 << PB1); // Мигаем светодиодом
}

ISR(USART0_DRE_vect) {
  // Обработка прерывания по готовности передачи данных USART0
  // Делаем что-то когда регистр данных готов к передаче
  PORTB ^= (1 << PB2); // Мигаем светодиодом
}

int main() {
  // Инициализация USART0
  UBRR0L = 0x67; // Настраиваем скорость передачи данных
  UBRR0H = 0x00;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Включаем приём и передачу данных
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Настраиваем формат данных

  // Включаем прерывания USART0
  UCSR0B |= (1 << RXCIE0); // Включаем прерывание по приёму данных
  UCSR0B |= (1 << TXCIE0); // Включаем прерывание по передаче данных
  UCSR0B |= (1 << UDRIE0); // Включаем прерывание по готовности передачи данных

  // Глобально включаем прерывания
  sei();

  while (1) {
    // Основной цикл программы
  }

  return 0;
}
В этом примере мы включаем прерывания по приёму данных, передаче данных и готовности передачи данных для USART0. Обработчики прерываний просто мигают светодиодами, но вы можете заменить это на любой другой код, который вам нужен.

Обратите внимание, что вы должны включить глобальные прерывания с помощью функции sei() перед тем, как прерывания начнут работать.