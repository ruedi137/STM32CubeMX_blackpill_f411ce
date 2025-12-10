
#include "serial_printf.h"

#include <stdarg.h>  // Für va_list, va_start, va_end
#include <stdio.h>   // Für vsnprintf
#include "usbd_cdc_if.h" // Für USB-Funktionen

#define PRINTF_BUFFER_SIZE 256 // Größe des Puffers für die formatierte Zeichenkette

// Extern: Die USB-Handle, die in usbd_conf.c oder usbd_cdc_if.c definiert ist.
extern USBD_HandleTypeDef hUsbDeviceFS;

/**
 * @brief Sendet einen Datenpuffer über den USB CDC (Virtual COM Port).
 * @param buf: Pointer auf den zu sendenden Puffer.
 * @param len: Länge des zu sendenden Puffers.
 * @retval USBD_OK wenn erfolgreich.
 */
uint8_t USB_Send_Buffer(uint8_t *buf, uint16_t len)
{
    // Optional: Kurz prüfen, ob das Gerät bereit ist.
    if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED)
    {
        return USBD_FAIL;
    }

    // Wartet, bis der USB-Stack die Daten erfolgreich sendet.
    uint8_t status;
    do {
        status = CDC_Transmit_FS(buf, len);
        
        // Fügt eine kurze Verzögerung ein, um die CPU nicht zu überlasten
        // und dem USB-Stack Zeit zur Abarbeitung zu geben.
        if (status == USBD_BUSY) {
            HAL_Delay(1);
        }
    } while (status == USBD_BUSY);

    return status; // Gibt USBD_OK oder USBD_FAIL zurück
}


/**
 * @brief Eine eigene printf-Implementierung, die direkt über USB CDC ausgibt.
 */
void myprintf(const char *format, ...)
{
    char print_buffer[PRINTF_BUFFER_SIZE];
    va_list args;
    int len;

    // 1. Variadische Argumente initialisieren
    va_start(args, format);

    // 2. Formatieren der Zeichenkette in einen Puffer mit Längenbegrenzung
    // Hier wird die eigentliche printf-Logik ausgeführt, ohne __io_putchar zu verwenden.
    len = vsnprintf(print_buffer, PRINTF_BUFFER_SIZE, format, args);

    // 3. Variadische Argumente bereinigen
    va_end(args);

    // 4. Prüfen, ob die Formatierung erfolgreich war und Daten vorhanden sind
    if (len > 0)
    {
        // Sicherstellen, dass die Länge den Puffer nicht überschreitet
        if (len >= PRINTF_BUFFER_SIZE) {
            len = PRINTF_BUFFER_SIZE - 1; // Kürzen, falls Buffer voll
        }
        
        // 5. Den Puffer über USB senden
        // Konvertierung in uint8_t* ist notwendig für die CDC-Schnittstelle
        USB_Send_Buffer((uint8_t *)print_buffer, (uint16_t)len);
    }
}