#ifndef ATA8520E_HPP
#define ATA8520E_HPP

#include "../hal/hal.h"
#include "../tools/data_types/byte_types.h"    

#include "ata8520e_regs.h"
#include "ata8520e_settings.h"

typedef struct Ata8520eInterface {
    spi_t spiDev;
    spi_clk_t spiClk;
    gpio_t nss;
    gpio_t int_;
    gpio_t power;
    gpio_t reset;
} Ata8520eInterface;


// ===== Also requires Sigfox interface, have merged this with main libsoilar branch yet ======

#define SIGFOX_MODE_ON                           true
#define SIGFOX_MODE_OFF                          false
#define SIGFOX_RESET_MODE_SYSTEM                 0U
#define SIGFOX_RESET_MODE_CHIP                   1U
#define SIGFOX_STATUS_MODE_SYSTEM                0U
#define SIGFOX_STATUS_MODE_CHIP                  1U
#define SIGFOX_STATUS_MODE_ALL                   2U

#define SD_MAX_INSTANCES                         1U

typedef struct SigfoxDevice {
    void (*printStatus)(uint8_t);
    void (*sendCmd)(uint8_t);
    void (*reset)(uint8_t);
    void (*setMode)(bool);
    void (*read)(uint8_t*, uint8_t);
    void (*send)(uint8_t*, uint8_t);
} SigfoxDevice;


// ==============================================================================================

void printStatusAta8520e(uint8_t statusMode);
void sendCmdAta8520e(uint8_t cmd);
void resetAta8520e(uint8_t resetMode);
void setModeAta8520e(uint8_t deviceMode);
void readAta8520e(uint8_t* buff, uint8_t size);
void sendAta8520e(uint8_t* buff, uint8_t size);

bool CreateAta8520e(SigfoxDevice* self, Ata8520eInterface* interface);

/////////////

bool _initAta8520e(void);
void _printChipStatusAta8520e(uint8_t mask);
void _printSystemStatusAta8520e(uint8_t mask);

uint8_t _singleTransferAta8520e(uint8_t value);
void _multiTransferAta8520e(uint8_t* output, uint8_t* input, uint8_t size);

void _resetSystemAta8520e(void);
void _resetChipAta8520e(void);

void _prepareAta8520e(uint8_t* msg, uint8_t size);


#endif /* ATA8520E_HPP */
