#pragma once

#include "Base.h"
#include "GraphicDevice.h"
#include "Renderer.h"

class CManagement : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	CManagement();
	virtual ~CManagement() = default;

public: /* For.General */
	HRESULT Ready_Engine(_uint iSceneCount);
	_uint Update_Engine();
	HRESULT Render_Engine();
	HRESULT Clear_ForScene(_uint iSceneIndex);


public:	/* For.Device Manager */
	LPDIRECT3DDEVICE9 Get_Device() const;

public: /* For.Scene Manager */
	HRESULT SetUp_CurrentScene(_int iSceneID, class CScene* pNextScene);

public: /* For.Renderer */
	HRESULT Add_GameObjectToRenderList(ERenderID eRenderID, class CGameObject* pGameObject);

public: /* For.GameObject Manager */
	HRESULT Add_GameObject_Prototype(_uint iSceneIndex, const wstring& PrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject_ToLayer(_uint iFromSceneIndex, const wstring& PrototypeTag, _uint iToSceneIndex, const wstring& LayerTag, void* pArg = nullptr);

public: /* For.Component Manager */
	HRESULT Add_Component_Prototype(_uint iSceneIndex, const wstring& PrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iSceneIndex, const wstring& PrototypeTag, void* pArg = nullptr);

public:
	virtual void Free() override;

private:
	CGraphicDevice*	m_pDevice_Manager = nullptr;
	CRenderer* m_pRenderer = nullptr;
	class CScene_Manager* m_pScene_Manager = nullptr;
	class CGameObject_Manager* m_pGameObject_Manager = nullptr;
	class CComponent_Manager* m_pComponent_Manager = nullptr;
};
