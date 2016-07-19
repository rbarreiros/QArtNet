#ifndef COMMON_H
#define COMMON_H

#ifdef _MSC_VER
    #define PACKED
    #pragma pack(push,1)
#else
    #define PACKED __attribute__((packed))
#endif

#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))

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

// m_status bit 7-8
typedef enum
{
    STATUS_INDICATOR_UNKNOWN = 0,
    STATUS_INDICATOR_LOCATE,
    STATUS_INDICATOR_MUTE,
    STATUS_INDICATOR_NORMAL
} artnet_status_indicator_t;

// m_status bit 5-6
typedef enum
{
    STATUS_PORTAUTH_UNKNOWN = 0,
    STATUS_PORTAUTH_PANEL,
    STATUS_PORTAUTH_NETWORK,
    STATUS_PORTAUTH_NOTUSED
} artnet_status_progauth_t;

// m_status bit 3
typedef enum
{
    STATUS_BOOT_FIRMWARE = 0,
    STATUS_BOOT_ROM
} artnet_status_boot_t;

// m_status bit 2
typedef enum
{
    STATUS_RDM_NOT_CAPABLE = 0,
    STATUS_RDM_CAPABLE
} artnet_status_rdm_t;

//m_status bit 1
typedef enum
{
    STATUS_UBEA_CORRUPT = 0,
    STATUS_UBEA_OK
} artnet_status_ubea_t;

// m_goodinput
typedef enum
{
    ARTNET_GI_ERRORS          = (1 << 3),
    ARTNET_GI_INPUT_DISABLED  = (1 << 4),
    ARTNET_GI_INC_DMX512_TEXT = (1 << 5),
    ARTNET_GI_INC_DMX512_SIP  = (1 << 6),
    ARTNET_GI_INC_DMX512_TEST = (1 << 7),
    ARTNET_GI_DATA_RECEIVED   = (1 << 8)
} artnet_goodinput_t;

// m_goodoutput
typedef enum
{
    ARTNET_GO_MERGE_LTP         = (1 << 2),
    ARTNET_GO_DMXOUT_SHORTCUT   = (1 << 3),
    ARTNET_GO_DMX_MERGING       = (1 << 4),
    ARTNET_GO_INC_DMX512_TEXT   = (1 << 5),
    ARTNET_GO_INC_DMX512_SIP    = (1 << 6),
    ARTNET_GO_INC_DMX512_TEST   = (1 << 7),
    ARTNET_GO_DATA_TRANSMITTING = (1 << 8)
} artnet_goodoutput_t;

typedef enum
{
    ARTNET_SUPPORT_BROWSER_CONFIG = (1 << 1),
    ARTNET_NODE_IP_CONFIG_MANUAL  = (1 << 2), // 0 = manual, 1 = dhcp
    ARTNET_NODE_DHCP_CAPABLE      = (1 << 3),
    ARTNET_NODE_V2                = (1 << 4), // 0 - v2, 1 - v3
} artnet_status2_t;

#define ARTNET_OP_REPLY 0x2100

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

typedef enum artnet_packet_type_e artnet_packet_type_t;

#endif // COMMON_H
