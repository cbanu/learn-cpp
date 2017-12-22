#include <iostream>
#include <string>
#include <map>

enum class eE : uint8_t {
	kA = 1 << 0,
	kB = 1 << 1,
	kC = 1 << 2
};

eE operator | (eE a, eE b) {
	return static_cast<eE>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

eE operator & (eE a, eE b) {
	return static_cast<eE>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

static const std::string kNone = "";
static const std::string kAStr = "A";
static const std::string kBStr = "B";
static const std::string kCStr = "C";

static const std::map<eE, std::string> eToStr = {
	{ eE::kA, kAStr},
	{ eE::kB, kBStr},
	{ eE::kC, kCStr}
};

static const std::map<std::string, eE> strToE = {
	{ kAStr, eE::kA},
	{ kBStr, eE::kB},
	{ kCStr, eE::kC}
};

class E
{
	public:
		static const std::string &ToString(eE e);
		static eE FromString(const std::string &s);
};

const std::string &E::ToString(eE e)
{
	std::map<eE, std::string>::const_iterator search = eToStr.find(e);
	if (search == eToStr.end()) {
		throw std::invalid_argument("invalid enum value");
	}
	return search->second;
}

eE E::FromString(const std::string &s)
{
	std::map<std::string, eE>::const_iterator search = strToE.find(s);
	if (search == strToE.end()) {
		throw std::invalid_argument("invalid string value");
	}
	return search->second;
}

int main() {
	std::cout << "Test..." << std::endl;
	eE x = eE::kB | eE::kA;
	//std::cout << x << std::endl;
	try {
		std::cout << E::ToString(x) << std::endl;
	} catch (std::exception &ex) {
		fprintf(stderr, "caught exception: %s\n", ex.what());
	}
	if ((x & eE::kB) == eE::kB) {
		printf("x has B\n");
	}
	//std::cout << E::FromString(kAStr) << std::endl;
}
