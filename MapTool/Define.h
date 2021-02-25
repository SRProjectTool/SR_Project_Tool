#pragma once

#define DEFAULT = default
#define NONE {}
#define WINCX 1600
#define WINCY 900
#define TILECX 130
#define TILECY 68
#define TILEX 1
#define TILEY 1

#define NO_EVENT 0
#define CHANGE_SCENE 1

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define GRAVITY			_float3(0,  -0.09807f, 0)
#define FLOAT3_ZERO		_float3(0,  0,  0)
#define FLOAT3_ONE		_float3(1,  1,  1)
#define FLOAT3_RIGHT	_float3(1,  0,  0)
#define FLOAT3_LEFT		_float3(-1, 0,  0)
#define FLOAT3_UP		_float3(0,  1,  0)
#define FLOAT3_DOWN		_float3(0,  -1, 0)
#define FLOAT3_FORWARD	_float3(0,  0,  1)
#define FLOAT3_BACK		_float3(0,  0, -1)

/**************************Smart Pointer****************************/
#define SHARED(typeName) shared_ptr<typeName>
#define UNIQUE(typeName) unique_ptr<typeName>
#define WEAK(typeName) weak_ptr<typeName>

#define SMART_DELETER_REGISTER														\
template<typename T> friend void SmartDeleter(T* something);
/*******************************************************************/

/****************************Message Box****************************/
#define MSG_BOX(msg) AfxMessageBox(msg)
/*******************************************************************/

/****************************Safe Delete****************************/
#define SAFE_DELETE(ptr)												\
if(ptr != nullptr)														\
{																		\
	delete ptr;															\
	ptr = nullptr;														\
}
/*******************************************************************/

/**************************Gettor / Settor**************************/
#define GETTOR_SETTOR(varType, varName, varInitValue, funcName)			\
protected:															    \
	varType varName = varInitValue; 									\
public: 															    \
	virtual inline varType& Get##funcName(void) { return varName; }     \
	virtual inline void Set##funcName(varType var){ varName = var; }    

#define GETTOR(varType, varName, varInitValue, funcName)				\
protected: 															    \
	varType varName = varInitValue; 									\
public: 															    \
	virtual inline varType& Get##funcName(void) { return varName; }
/*******************************************************************/

/**************************Singleton Macro**************************/
//카피 생성자를 막아용
#define NO_COPY(ClassName)												\
private:																\
	ClassName(const ClassName&)	= delete;

//Assign operator도 막아용
#define NO_ASSIGN_OPERATOR(ClassName)									\
private:																\
	ClassName& operator=(const ClassName&) = delete;

//Default Destructor 매크로
#define DEFAULT_DESTRUCTOR(ClassName)									\
	virtual ~ClassName(void) DEFAULT;									

//Default Constructor 매크로
#define DEFAULT_CONSTRUCTOR(ClassName)									\
	explicit ClassName(void) NONE;										

#define DEFAULT_COPY_CONSTRUCTOR(ClassName)								\
	explicit ClassName(const ClassName& other) NONE;

//싱글턴 선언 매크로
#define DECLARE_SINGLETON(ClassName)									\
		NO_COPY(ClassName)												\
public:																	\
	static ClassName* GetInstance();									\
	static _uint DestroyInstance();										\
private:																\
	static ClassName* m_pInstance;


//싱글턴 정의 매크로
#define IMPLEMENT_SINGLETON(ClassName)									\
ClassName* ClassName::m_pInstance = nullptr;							\
ClassName* ClassName::GetInstance()										\
{																		\
	if (nullptr == m_pInstance)											\
	{																	\
		m_pInstance = new ClassName;									\
	}																	\
	return m_pInstance;													\
}																		\
_uint ClassName::DestroyInstance()										\
{																		\
	_uint iRefCount = 0;												\
	if (m_pInstance)													\
	{																	\
		iRefCount = m_pInstance->Release();								\
		m_pInstance = nullptr;											\
	}																	\
	return iRefCount;													\
}
/*******************************************************************/

#define GET_DEVICE CGraphicDevice::GetInstance()->GetDevice()

//FRC Macro
#define GET_DT CFRC::GetInstance()->GetDeltaTime()
