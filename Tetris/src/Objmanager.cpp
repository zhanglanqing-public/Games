#include "Objmanager.h"
#include "antiObj.h"
#include "antizagObj.h"
#include "BarObj.h"
#include "Buffer.h"
#include "LObj.h"
#include "Object.h"
#include "crossObj.h"
#include "sqrtObj.h"
#include "zagObj.h"

void ObjectManager::Init() {
	static auto generator =
			std::default_random_engine(static_cast<unsigned int>(time(0)));
	int i = generator() % 7;
	
	switch (i) {
	case 0: {
		obj = new BarObj(hp); break;
			}
	case 1: {
		obj = new LObj(hp); break;
			}
	case 2: {
		obj = new antiLObj(hp); break;
			}
	case 3: {
		obj = new ZagObj(hp); break;
			}
	case 4: {
		obj = new antiZagObj(hp); break;
			}
	case 5: {
		obj = new sqrtObj(hp); break;
			}
	case  6: {
		obj = new crossObj(hp); break;
			 }
	}
}

void ObjectManager::SetColor(const Color& color) {
	auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color.ToWindowsColor());
}
