#ifndef __EEPROM_EMUL_CONF_H
#define __EEPROM_EMUL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* At 512K flash we have 255 pages, so we're generously reserving the last 10:
 * 2 pages for 2 (* 10K cycles) * 2 + 2 guard pages (=10)
 * With a pages size of 2K, that's 20K
 */

/* Start address of the 1st page in flash, for EEPROM emulation */
#define START_PAGE_ADDRESS 0x0807b000U

/* Number of 10Kcycles requested, minimum 1 for 10Kcycles (default), for instance
 * 10 to reach 100Kcycles. This factor will increase pages number */
#define CYCLES_NUMBER 2U

/* Number of guard pages avoiding frequent transfers (must be multiple of 2):
 * 0,2,4.. */
#define GUARD_PAGES_NUMBER 2U

/* Configuration of crc calculation for eeprom emulation in flash */
/* CRC polynomial lenght 16 bits */
#define CRC_POLYNOMIAL_LENGTH LL_CRC_POLYLENGTH_16B
/* Polynomial to use for CRC calculation */
#define CRC_POLYNOMIAL_VALUE 0x8005U
/* Number of variables to handle in eeprom */
#define NB_OF_VARIABLES 10U

#ifdef __cplusplus
}
#endif

#endif /* __EEPROM_EMUL_CONF_H */

