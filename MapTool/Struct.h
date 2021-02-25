#pragma once

typedef struct _CustomVertex
{
	_float3 position;
	_float3 normal;
	_float2 uv;
} CUSTOM_VERTEX;

typedef struct _MeshData
{
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	_uint vertexCount;
	_uint veertexSize;
	_uint faceCount;
	_uint FVF;
	_uint vertexNumInFace;

	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	D3DFORMAT indexFormat;
	_uint indexSize;
} MESH_DATA;

typedef struct _TextureData
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO imageInfo;
} TEXTURE_DATA;

typedef struct _BOOL3
{
	_BOOL3(_bool x, _bool y, _bool z)
	{
		x = x;
		y = y;
		z = z;
	}

	_bool x;
	_bool y;
	_bool z;
} BOOL3;

typedef struct _Face
{
	_uint vertexIndex[3];
	_uint uvIndex[3];
	_uint normIndex[3];
} FACE;

typedef struct _VertexColor
{
	_float3 vPosition;
	_uint iColor;
} VTX_COLOR;

const _uint FVF_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct _VertexTexture
{
	_float3 vPosition;
	_float2 vUV;
} VTX_TEXTURE;

typedef struct _VertexCubeTexture
{
	_float3 vPosition;
	_float3 vUV;
} VTXCUBE_TEXTURE;

const _uint FVF_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1;

const _uint FVF_CUBETEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct Index16
{
	WORD _1, _2, _3;
} INDEX16;

typedef struct Index32
{
	WORD _1, _2, _3;
} INDEX32;