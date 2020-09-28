#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <string>
#include <sstream>
#include "Variant.hpp"
#include "rtRect.h"
using std::string;

template< class C>
std::string get_str(C value)
{
	std::ostringstream o;
	o << value;
	return o.str();
}
string print_2(CL_Vec2f v)
{
	char st[128];
	sprintf_s(st, "%.2f, %.2f", v.x, v.y);
	return string(st);
}

string print_3(CL_Vec3f v)
{
	char st[128];
	sprintf_s(st, "%.3f, %.3f, %.3f", v.x, v.y, v.z);
	return string(st);
}

string print_4(CL_Rectf v)
{
	char st[128];
	sprintf_s(st, "%.3f, %.3f, %.3f, %.3f", v.left, v.top, v.right, v.bottom);
	return string(st);
}

string print_4(rtRectf v)
{
	char st[128];
	sprintf_s(st, "%.3f, %.3f, %.3f, %.3f", v.left, v.top, v.right, v.bottom);
	return string(st);
}

Variant::~Variant()
{
}

void Variant::Set(std::string const& var)
{
	m_type = type_c;
	m_string = var;
}

void Variant::SetVariant(Variant* pVar) //needed this because boost was confused...
{
	Set(*pVar);
}

void Variant::Set(const Variant& v)
{

	//update our data from another variant object
	switch (v.get())
	{
	case type_b:
		Set(v.get_y());
		break;
	case type_c:
		Set(v.get_h());
		break;
	case type_d:
		Set(v.get_g());
		break;
	case type_e:
		Set(v.get_p());
		break;
	case type_f:
		Set(v.get_d());
		break;
	case type_z:
		Set(v.get_a());
		break;
	case type_g:
		Set(v.get_b());
		break;
	case type_x:
		Set(v.get_m());
		break;
	case type_y:
		Set(v.get_q());
		break;

	default:break;
	}

}

Variant& Variant::operator+=(const Variant& rhs)
{
	if (get() == rhs.get())
	{
		switch (get())
		{
		case type_b:
			Set(get_y() + rhs.get_y());
			break;

		case type_c:
			Set(get_h() + rhs.get_h());
			break;

		case type_d:
			Set(get_g() + rhs.get_g());
			break;

		case type_e:
			Set(get_p() + rhs.get_p());
			break;

		case type_f:
			Set(get_d() + rhs.get_d());
			break;

		case type_z:
			Set(get_a() + rhs.get_a());
			break;

		default:
			break;
		}
	}

	return *this;
}

Variant& Variant::operator-=(const Variant& rhs)
{
	if (get() == rhs.get())
	{
		switch (get())
		{
		case type_b:
			Set(get_y() - rhs.get_y());
			break;

		case type_d:
			Set(get_g() - rhs.get_g());
			break;

		case type_e:
			Set(get_p() - rhs.get_p());
			break;

		case type_f:
			Set(get_d() - rhs.get_d());
			break;

		case type_z:
			Set(get_a() - rhs.get_a());
			break;

		default:
			break;
		}
	}

	return *this;
}

bool Variant::operator==(const Variant& rhs) const
{
	if (get() != rhs.get()) {
		return false;
	}

	switch (get())
	{
	case type_a:
		return true;

	case type_b:
		return get_y() == rhs.get_y();

	case type_c:
		return get_h() == rhs.get_h();

	case type_d:
		return get_g() == rhs.get_g();

	case type_e:
		return get_p() == rhs.get_p();

	case type_f:
		return get_d() == rhs.get_d();

	case type_g:
		return get_b() == rhs.get_b();

	case type_x:
		return get_m() == rhs.get_m();

	case type_y:
		return get_q() == rhs.get_q();

	case type_z:
		return get_a() == rhs.get_a();

	default:
		return false;
	}
}

bool Variant::operator!=(const Variant& rhs) const
{
	return !operator==(rhs);
}

std::string Variant::Print()
{
	switch (get())
	{
	case type_b:
		return get_str(get_y());
		break;
	case type_c:
		return get_h();
		break;

	case type_d:
		return print_2(get_g());
		break;
	case type_e:
		return print_3(get_p());
		break;

	case type_f:
		return get_str(get_d());
		break;
	case type_z:
		return get_str(get_a());
		break;
	case type_g:
		return "entity";
		break;
	case type_x:
		return "component";
		break;
	case type_y:
		return print_4(get_q());
		break;
	default:
		return "Unknown";
		break;
	}

	return "Unknown";
}

inline Variant operator+(Variant lhs, const Variant& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Variant operator-(Variant lhs, const Variant& rhs)
{
	lhs -= rhs;
	return lhs;
}
