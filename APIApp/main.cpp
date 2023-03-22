#include <Windows.h>
#include <GameEngineContents/WormsCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	WormsCore::GetInst()->CoreStart(hInstance);

	return 1;
}