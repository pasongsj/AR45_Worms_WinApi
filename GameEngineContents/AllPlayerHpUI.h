#pragma once

// Ό³Έν :
class AllPlayerHpUI
{
public:
	// constrcuter destructer
	AllPlayerHpUI();
	~AllPlayerHpUI();

	// delete Function
	AllPlayerHpUI(const AllPlayerHpUI& _Other) = delete;
	AllPlayerHpUI(AllPlayerHpUI&& _Other) noexcept = delete;
	AllPlayerHpUI& operator=(const AllPlayerHpUI& _Other) = delete;
	AllPlayerHpUI& operator=(AllPlayerHpUI&& _Other) noexcept = delete;

protected:

private:

};

