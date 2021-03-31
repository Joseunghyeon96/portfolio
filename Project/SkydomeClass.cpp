#include "SkydomeClass.h"

#include <fstream>
using namespace std;


SkyDomeClass::SkyDomeClass()
{
	time = 360;
}


SkyDomeClass::SkyDomeClass(const SkyDomeClass& other)
{
}


SkyDomeClass::~SkyDomeClass()
{
}


bool SkyDomeClass::Initialize(ID3D11Device* device)
{
	// ��ī�� �� �� ������ �о�ɴϴ�.
	if (!LoadSkyDomeModel("../Project/data/skydome.txt"))
	{
		return false;
	}

	// ��ī�� ���� ������ �ε��ϰ� �������� ���� �ε��� ���۸� �ε��մϴ�.
	if (!InitializeBuffers(device))
	{
		return false;
	}
	sunsetApexColor = D3DXVECTOR4(0.780f, 0.153f, 0.153f, 1.0f);
	sunsetCenterColor = D3DXVECTOR4(0.992f, 0.839f, 0.511f, 1.0f);
	nightApexColor = D3DXVECTOR4(0.096f, 0.101f, 0.176f, 1.0f);
	nightCenterColor = D3DXVECTOR4(0.141f, 0.181f, 0.197f, 0.7f);
	dayApexColor = D3DXVECTOR4(0.53f, 0.81f, 0.92f, 1.0f);
	dayCenterColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);


	dayToSunsetApex = (sunsetApexColor - dayApexColor) / 60;
	dayToSunsetCenter = (sunsetCenterColor - dayCenterColor) / 60;
	sunsetToDayApex = (dayApexColor - sunsetApexColor) / 60;
	sunsetToDayCenter = (dayCenterColor - sunsetCenterColor) / 60;

	nightToSunsetApex = (sunsetApexColor - nightApexColor) / 60;
	nightToSunsetCenter = (sunsetCenterColor - nightCenterColor) / 60;
	sunsetToNightApex = (nightApexColor - sunsetApexColor) / 60;
	sunsetToNightCenter = (nightCenterColor - sunsetCenterColor) / 60;

	time = 360;
	//==== ��
	// ��ī�� �� ����⿡ ������ �����մϴ�.
	m_apexColor = dayApexColor;

	// ��ī�� ���� �߽ɿ� ������ �����մϴ�.
	m_centerColor = dayCenterColor;


	return true;
}


void SkyDomeClass::Shutdown()
{
	// ��ī�� �� �������� ���� ���� �� �ε��� ���۸� �����մϴ�.
	ReleaseBuffers();

	// ��ī�� �� ���� �����մϴ�.
	ReleaseSkyDomeModel();
}


void SkyDomeClass::Render(ID3D11DeviceContext* deviceContext)
{
	// ��ī�� ���� ������ �մϴ�.
	RenderBuffers(deviceContext);
}


int SkyDomeClass::GetIndexCount()
{
	return m_indexCount;
}


D3DXVECTOR4 SkyDomeClass::GetApexColor()
{
	return m_apexColor;
}


D3DXVECTOR4 SkyDomeClass::GetCenterColor()
{
	return m_centerColor;
}

void SkyDomeClass::Frame()
{
	time++;

	if (time > 1440)
		time = 0;

	SkyChange();
}

void SkyDomeClass::SkyChange()
{
	if (time < 300) // 5�� ������ ��
	{
		m_apexColor = nightApexColor;
		m_centerColor = nightCenterColor;
	}
	else if (time >= 300 && time < 360) // 5~6�ñ��� ��-> ������ �ٲ�
	{
		m_apexColor += nightToSunsetApex;
		m_centerColor += nightToSunsetCenter;
	}
	else if (time >= 360 && time < 420) //6�� ~7�ñ��� ����
	{
		m_apexColor = sunsetApexColor;
		m_centerColor = sunsetCenterColor;
	}
	else if (time >= 420 && time < 480) // 7�� ~ 8�ñ��� ���� -> ��ħ���ιٲ�
	{
		m_apexColor += sunsetToDayApex;
		m_centerColor += sunsetToDayCenter;
	}
	else if (time >= 480 && time < 1020) // 8�� ~ 17�ñ��� ���� �ϴ�
	{
		m_apexColor = dayApexColor;
		m_centerColor = dayCenterColor;
	}
	else if (time >= 1020 && time < 1080) // 17�� ~ 18�ñ��� ���� �ϴ� -> ����
	{
		m_apexColor += dayToSunsetApex;
		m_centerColor += dayToSunsetCenter;
	}
	else if (time >= 1080 && time < 1140) // 18�� ~ 19�ñ��� ���� -> ��
	{
		m_apexColor += sunsetToNightApex;
		m_centerColor += sunsetToNightCenter;
	}
	else if (time >= 1140)
	{
		m_apexColor = nightApexColor;
		m_centerColor = nightCenterColor;
	}
}

bool SkyDomeClass::IsSpecularLite()
{
	return false;
}

int SkyDomeClass::GetTime()
{
	return time;
}


bool SkyDomeClass::LoadSkyDomeModel(const char* filename)
{
	// �� ������ ���ϴ�.
	ifstream fin;
	fin.open(filename);

	// ������ �� �� ������ �����մϴ�.
	if (fin.fail())
	{
		return false;
	}

	// ���ؽ� ī��Ʈ�� ������ �д´�.
	char input = 0;
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// ���ؽ� ī��Ʈ�� �д´�.
	fin >> m_vertexCount;

	// �ε����� ���� ���� ���� ���� �����մϴ�.
	m_indexCount = m_vertexCount;

	// �о� ���� ���� ������ ����Ͽ� ���� ����ϴ�.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// �������� ���� �κб��� �д´�.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// ���ؽ� �����͸� �н��ϴ�.
	for (int i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// �� ������ �ݴ´�.
	fin.close();

	return true;
}


void SkyDomeClass::ReleaseSkyDomeModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}
}


bool SkyDomeClass::InitializeBuffers(ID3D11Device* device)
{
	// ���� �迭�� ����ϴ�.
	VertexType* vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// �ε��� �迭�� ����ϴ�.
	unsigned long* indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// ���� �迭�� �ε��� �迭�� �����ͷ� �ε��մϴ�.
	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		indices[i] = i;
	}

	// ���� ������ ����ü�� �����Ѵ�.
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// subresource ������ ���� �����Ϳ� ���� �����͸� �����մϴ�.
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// ���� ��ħ�� ���� ���۸� ����ϴ�.
	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	// �ε��� ������ ����ü�� �����մϴ�.
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// ���� ���ҽ� ������ �ε��� �����Ϳ� ���� �����͸� �����մϴ�.
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// �ε��� ���۸� ����ϴ�.
	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	// ���� ���ؽ��� �ε��� ���۰� �����ǰ�ε� �� �迭�� �����Ͻʽÿ�.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}


void SkyDomeClass::ReleaseBuffers()
{
	// �ε��� ���۸� �����մϴ�.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// ���ؽ� ���۸� �����Ѵ�.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void SkyDomeClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// ���� ���� ���� �� �������� �����մϴ�.
	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;

	// ������ �� �� �ֵ��� �Է� ��������� ���� ���۸� Ȱ������ �����մϴ�.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// ������ �� �� �ֵ��� �Է� ��������� �ε��� ���۸� Ȱ������ �����մϴ�.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �� ������ ���ۿ��� �������Ǿ���ϴ� ������Ƽ�� ������ �����մϴ�.�� ��쿡�� �ﰢ���Դϴ�.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

