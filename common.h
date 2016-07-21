#ifndef COMMON_H
#define COMMON_H

#ifdef _MSC_VER
    #define PACKED
    #pragma pack(push,1)
#else
    #define PACKED __attribute__((packed))
#endif

#ifndef bswap_16
#define bswap_16(x)  ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))
#endif

#ifdef HAVE_ENDIAN_H
# if BYTE_ORDER == __BIG_ENDIAN
#  define htols(x)   bswap_16 (x)
# else
#  define htols(x)  (x)
# endif
#else
# if BYTE_ORDER == BIG_ENDIAN
#  define htols(x)   bswap_16 (x)
# else
#  define htols(x)  (x)
# endif
#endif

#define OEM     0x0431
#define ESTAMAN 0x5944

#define ARTNET_STRING  "Art-Net\0"
#define ARTNET_STRING_SIZE       8
#define ARTNET_UDP_PORT       6454
#define ARTNET_MAX_PORTS         4  // Always 4
#define ARTNET_SHORTNAME_LENGTH 18
#define ARTNET_LONGNAME_LENGTH  64
#define ARTNET_REPORT_LENGTH    64
#define ARTNET_DMX_LENGTH      512
#define ARTNET_RDM_UID_WIDTH     6
#define ARTNET_MAC_SIZE          6
#define ARTNET_ESTA_SIZE         2
#define ARTNET_IP_SIZE           4
#define ARTNET_VERSION          14


typedef enum
{
    ARTNET_ENABLE_INPUT  = 0x40,
    ARTNET_ENABLE_OUTPUT = 0x80
} artnet_port_settings_t;

typedef enum
{
    ARTNET_PORT_DMX    = 0x00,
    ARTNET_PORT_MIDI   = 0x01,
    ARTNET_PORT_AVAB   = 0x02,
    ARTNET_PORT_CMX    = 0x03,
    ARTNET_PORT_ADB    = 0x04,
    ARTNET_PORT_ARTNET = 0x05
} artnet_port_data_code;

typedef enum
{
    ARTNET_PC_NONE        = 0x00,
    ARTNET_PC_CANCEL      = 0x01,
    ARTNET_PC_LED_NORMAL  = 0x02,
    ARTNET_PC_LED_MUTE    = 0x03,
    ARTNET_PC_LED_LOCATE  = 0x04,
    ARTNET_PC_RESET       = 0x05,
    ARTNET_PC_MERGE_LTP_O = 0x10,
    ARTNET_PC_MERGE_LTP_1 = 0x11,
    ARTNET_PC_MERGE_LTP_2 = 0x12,
    ARTNET_PC_MERGE_LTP_3 = 0x13,
    ARTNET_PC_MERGE_HTP_0 = 0x50,
    ARTNET_PC_MERGE_HTP_1 = 0x51,
    ARTNET_PC_MERGE_HTP_2 = 0x52,
    ARTNET_PC_MERGE_HTP_3 = 0x53,
    ARTNET_PC_CLR_0       = 0x93,
    ARTNET_PC_CLR_1       = 0x93,
    ARTNET_PC_CLR_2       = 0x93,
    ARTNET_PC_CLR_3       = 0x93,
} artnet_port_cmd_t;

typedef enum
{
    ARTNET_FIRMWARE_BLOCKGOOD = 0x00,
    ARTNET_FIRMWARE_ALLGOOD   = 0x01,
    ARTNET_FIRMWARE_FAIL      = 0xff,
} artnet_firmware_status_code;

typedef enum
{
    ARTNET_TOD_FULL  = 0x00,
    ARTNET_TOD_FLUSH = 0x01,
} artnet_tod_command_code;

typedef enum
{
    ARTNET_INPUT_PORT = 1,
    ARTNET_OUTPUT_PORT,
} artnet_port_dir_t;

typedef enum
{
    ARTNET_SRV,     /**< An ArtNet server (transmitts DMX data) */
    ARTNET_NODE,    /**< An ArtNet node   (dmx reciever) */
    ARTNET_MSRV,    /**< A Media Server */
    ARTNET_ROUTE,   /**< No Effect currently */
    ARTNET_BACKUP,  /**< No Effect currently */
    ARTNET_RAW      /**< Raw Node - used for diagnostics */
} artnet_node_type;

typedef enum
{
    ARTNET_STATUS_DEBUG                 = 0x0000,
    ARTNET_STATUS_POWER_OK              = 0x0001,
    ARTNET_STATUS_POWER_FAIL            = 0x0002,
    ARTNET_STATUS_READ_FAIL             = 0x0003,
    ARTNET_STATUS_PARSE_FAIL            = 0x0004,
    ARTNET_STATUS_WRITE_FAIL            = 0x0005,
    ARTNET_STATUS_SHORT_NAME_SUCCESS    = 0x0006,
    ARTNET_STATUS_LONG_NAME_SUCCESS     = 0x0007,
    ARTNET_STATUS_DMX_ERRORS            = 0x0008,
    ARTNET_STATUS_WRITE_BUFFER_FULL     = 0x0009,
    ARTNET_STATUS_READ_BUFFER_FULL      = 0x000a,
    ARTNET_STATUS_UNIVERSE_CONFLICT     = 0x000b,
    ARTNET_STATUS_CONFIGURATION_FAIL    = 0x000c,
    ARTNET_STATUS_DMX_OUTPUT_SHORT      = 0x000d,
    ARTNET_STATUS_FIRMWARE_FAIL         = 0x000e,
    ARTNET_STATIS_USER_FAIL             = 0x000f
} artnet_node_status_t;



enum artnet_packet_type_e
{
  ARTNET_POLL               = 0x2000,
  ARTNET_REPLY              = 0x2100,
  ARTNET_DMX                = 0x5000,
  ARTNET_ADDRESS            = 0x6000,
  ARTNET_INPUT              = 0x7000,
  ARTNET_TODREQUEST         = 0x8000,
  ARTNET_TODDATA            = 0x8100,
  ARTNET_TODCONTROL         = 0x8200,
  ARTNET_RDM                = 0x8300,
  ARTNET_VIDEOSETUP         = 0xa010,
  ARTNET_VIDEOPALETTE       = 0xa020,
  ARTNET_VIDEODATA          = 0xa040,
  ARTNET_MACMASTER          = 0xf000,
  ARTNET_MACSLAVE           = 0xf100,
  ARTNET_FIRMWAREMASTER     = 0xf200,
  ARTNET_FIRMWAREREPLY      = 0xf300,
  ARTNET_IPPROG             = 0xf800,
  ARTNET_IPREPLY            = 0xf900,
  ARTNET_MEDIA              = 0x9000,
  ARTNET_MEDIAPATCH         = 0x9200,
  ARTNET_MEDIACONTROLREPLY  = 0x9300
} PACKED;

#endif // COMMON_H
