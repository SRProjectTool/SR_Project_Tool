#include "stdafx.h"
#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(CGraphicDevice)

CGraphicDevice::CGraphicDevice()
{
}

LPDIRECT3DDEVICE9 CGraphicDevice::GetDevice() const
{
	return m_pDevice;
}

HRESULT CGraphicDevice::Ready_GraphicDevice()
{
	D3DCAPS9 DeviceCap;
	DWORD vp = 0;
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	if (nullptr == m_pSDK)
	{
		MSG_BOX(L"Failed To Init Direct3DCreate9");
		return E_FAIL;
	}

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		MSG_BOX(L"Create SDK Failed");
		return E_FAIL;
	}

	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWND;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp, &d3dpp, &m_pDevice)))
	{
		MSG_BOX(L"Failed To CreateDevice");
		return E_FAIL;
	}

	return S_OK;
}

void CGraphicDevice::Free()
{
	if (FAILED(Safe_Release(m_pDevice)))
	{
		MSG_BOX(L"Failed To Release m_pDevice");
	}

	if (FAILED(Safe_Release(m_pSDK)))
	{
		MSG_BOX(L"Failed To Release m_pSDK");
	}
}
