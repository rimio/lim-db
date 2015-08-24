#ifndef SCAN_HPP_
#define SCAN_HPP_

class Scan {
public:
	virtual void Start() = 0;
	virtual void End() = 0;
	virtual bool HasNext() = 0;
};

#endif