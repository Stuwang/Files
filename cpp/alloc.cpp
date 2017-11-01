#include <iostream>
#include <memory>

#define NO_TO_USED -1
#define USED  -1
#define NO_NEXT  -2

class IdMaster {
public:
	IdMaster() {
		head_ = 0;
		id_.reset(new short[1024]());
		for (int i = 0; i < 1024; ++i)
		{
			id_[i] = i + 1;
		}
		id_[1024 - 1] = NO_NEXT;
	};
	IdMaster(int size) {
		head_ = 0;
		id_.reset(new short[size]());
		for (int i = 0; i < size; ++i)
		{
			id_[i] = i + 1;
		}
		id_[size - 1] = NO_NEXT;
	};
	~IdMaster() {
	}
	short GetId() {
		if ( head_ == NO_NEXT ) {
			return NO_TO_USED;
		}
		short i = head_;
		head_ = id_[head_];
		id_[i] = USED;
		return i;
	}
	void PutId(short in) {
		id_[in] = head_;
		head_ = in;
	}

	IdMaster(const IdMaster&) = delete;
	IdMaster(IdMaster&&) = delete;
	IdMaster& operator=(const IdMaster&) = delete;
	IdMaster& operator=(IdMaster&&) = delete;
private:
	short head_;
	std::unique_ptr<short[]> id_;
};

int main() {
	IdMaster idm(10);
	while (true) {
		auto ret = idm.GetId();
		if (ret != NO_TO_USED) {
			std::cout << "Get Id " << ret << std::endl;
		} else {
			std::cout << "No To Use " << std::endl ;
			break;
		}
	}
}
