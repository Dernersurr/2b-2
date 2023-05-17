#pragma
// The clock, for timing (such as the game loop)
namespace df {
	class Clock {

	private:
		long int previous_time;  // Prev time delta() called (micro sec)

	public:
		// Sets previous_time to current time.
		Clock();

		// Return time elapsed since delta() was last called, -1 if error.
		// Units are microseconds.
		long int delta(void);

		// Return time elapsed since delta() was last called.
		// Units are microseconds.
		long int split(void) const;
	};
}