class HardwareSerial : public Stream
{
	private:
	
	protected:
		volatile uint8_t * const _ubrrh
		volatile uint8_t * const _ubrrl;
		volatile uint8_t * const _ucsra;
		volatile uint8_t * const _ucsrb;
		volatile uint8_t * const _ucsrc;
		volatile uint8_t * const _udr;
		// Has any byte been written to the UART since begin()
		bool _written;

		volatile rx_buffer_index_t _rx_buffer_head;
		volatile rx_buffer_index_t _rx_buffer_tail;
		volatile tx_buffer_index_t _tx_buffer_head;
		volatile tx_buffer_index_t _tx_buffer_tail;

		// Don't put any members after these buffers, since only the first
		// 32 bytes of this struct can be accessed quickly using the ldd
		// instruction.
		unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
		unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

	
	public:
		inline HardwareSerial(
		volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
		volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
		volatile uint8_t *ucsrc, volatile uint8_t *udr);
		void begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
		void begin(unsigned long, uint8_t);
		void end();
		virtual int available(void);
		virtual int peek(void);
		virtual int read(void);
		virtual int availableForWrite(void);
		virtual void flush(void);
		virtual size_t write(uint8_t);
		inline size_t write(unsigned long n) { return write((uint8_t)n); }
		inline size_t write(long n) { return write((uint8_t)n); }
		inline size_t write(unsigned int n) { return write((uint8_t)n); }
		inline size_t write(int n) { return write((uint8_t)n); }
		using Print::write; // pull in write(str) and write(buf, size) from Print
		operator bool() { return true; }

		// Interrupt handlers - Not intended to be called externally
		inline void _rx_complete_irq(void);
		void _tx_udr_empty_irq(void);

};
