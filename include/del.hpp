#ifndef DEL_H_
#define DEL_H_
namespace dell {
template<typename T, typename C>
static void del(T &str, C remove_key)
{
	auto copy = str.begin();
	for (auto src = str.cbegin(); src < str.cend(); ++src) {
		if (*src != remove_key) {
			*copy++ = *src;
		}
	}
	str.erase(copy, str.end());
}
}
#endif /* DEL_H_ */
