#pragma once
class WeaponFirePunch
{
public:
	// constrcuter destructer
	WeaponFirePunch() ;
	~WeaponFirePunch();

	// delete Function
	WeaponFirePunch(const WeaponFirePunch& _Other) = delete;
	WeaponFirePunch(WeaponFirePunch&& _Other) noexcept = delete;
	WeaponFirePunch& operator=(const WeaponFirePunch& _Other) = delete;
	WeaponFirePunch& operator=(WeaponFirePunch&& _Other) noexcept = delete;

protected:

private:

};

