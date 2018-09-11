/*
 * DATAGRAM STRUCTURE
 * 
 * <CMD, 1 byte><PAYLOAD, n bytes>(\r)\n
 * 
 */

#define SP_MIN_DATAGRAM_SIZE 2

#define SP_SET_BRIGHTNESS 'b'       //0x62
#define SP_SET_CLIMA 'c'            //0x63
#define SP_SET_PAGE 'p'         //0x70
#define SP_SET_VOLUME 'v'       //0x76

#define SP_COMMENT_PREFIX '/'   // 0x2F

// set Log Prefix
#define LOG_PREFIX SP_COMMENT_PREFIX
