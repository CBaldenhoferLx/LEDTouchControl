/*
 * DATAGRAM STRUCTURE
 * 
 * <CMD, 1 byte><PAYLOAD, n bytes>(\r)\n
 * 
 */

#define SP_MIN_DATAGRAM_SIZE 2

#define SP_BRIGHTNESS 'b'       //0x42

#define SP_COMMENT_PREFIX '/'   // 0x2F

// set Log Prefix
#define LOG_PREFIX SP_COMMENT_PREFIX
