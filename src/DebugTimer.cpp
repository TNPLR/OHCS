class TimerBaseClock {
public:

	//Clear the Timer
	TimerBaseClock(){
		m_start = -1;
	}

	//So does this
	void Clear(){
		m_start = -1;
	}
	
	bool IsStarted() const{
		return(m_start != -1);
	}
	void Start(){
		m_start = clock();
	}
	unsigned long GetMs(){
		clock_t now;
		if (IsStarted()){
			now = clock();
			clock_t dt = (now - m_start);
			return (unsigned long)(dt * 1000/ CLOCKS_PER_SEC);
		}
		return 0;
	}
private:
	clock_t m_start;
};
