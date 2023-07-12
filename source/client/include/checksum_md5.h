#pragma once

#define MD5_DIGEST_LENGTH 16  
#define MD5_BIT_LENGTH ( MD5_DIGEST_LENGTH * sizeof( unsigned char ) )

struct md5_value_t {
	unsigned char m_bits[ MD5_DIGEST_LENGTH ];

	void zero( );
	bool is_zero( ) const;

	bool operator==( const md5_value_t& src ) const;
	bool operator!=( const md5_value_t& src ) const;
};

typedef struct {
	unsigned int m_buf[ 4 ];
	unsigned int m_bits[ 2 ];
	unsigned char m_in[ 64 ];
} md5_context_t;

void md5_init( md5_context_t* context );
void md5_update( md5_context_t* context, unsigned char const* buf, unsigned int len );
void md5_final( unsigned char digest[ MD5_DIGEST_LENGTH ], md5_context_t* context );

unsigned int md5_pseudo_random( unsigned int seed );

bool md5_compare( const md5_value_t& data, const md5_value_t& compare );

inline bool md5_value_t::operator==( const md5_value_t& src ) const {
	return md5_compare( *this, src );
}

inline bool md5_value_t::operator!=( const md5_value_t& src ) const {
	return !md5_compare( *this, src );
}