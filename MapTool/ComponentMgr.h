#pragma once

#include "Component.h"

class CComponent_Manager : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)

private:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	HRESULT Ready_Component_Manager(_size iSceneCount);
	HRESULT Add_Component_Prototype(_uint iSceneIndex, const wstring& PrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iSceneIndex, const wstring& PrototypeTag, void* pArg = nullptr);
	HRESULT Clear_ForScene(_uint iSceneIndex);

public:
	virtual void Free() override;

private:
	typedef unordered_map<wstring, CComponent*>	COMPONENTS; /* 컴포넌트들의 원형들을 보관 */
	COMPONENTS*	m_pComponents = nullptr;	// 동적배열
	_size		m_iContainerSize = 0;
};

