#include "SkyPlaneClass.h"




SkyPlaneClass::SkyPlaneClass()
{
}


SkyPlaneClass::SkyPlaneClass(const SkyPlaneClass& other)
{
}


SkyPlaneClass::~SkyPlaneClass()
{
}


bool SkyPlaneClass::Initialize(ID3D11Device* device, const WCHAR* textureFilename1, const WCHAR* textureFilename2)
{
	// �ϴ� ��� �Ű� ������ �����մϴ�.
	int skyPlaneResolution = 10;
	int textureRepeat = 4;
	float skyPlaneWidth = 10.0f;
	float skyPlaneTop = 0.5f;
	float skyPlaneBottom = 0.0f;

	// ������ ��⸦ �����մϴ�.
	m_brightness = 0.65f;

	// ���� ��ȯ �ӵ� ������ �����մϴ�.
	m_translationSpeed[0] = 0.0003f;   // ù ��° �ؽ�ó X ��ȯ �ӵ�.
	m_translationSpeed[1] = 0.0f;      // ù ��° �ؽ�ó Z ��ȯ �ӵ�.
	m_translationSpeed[2] = 0.00015f;  // �� ��° �ؽ�ó X ��ȯ �ӵ�.
	m_translationSpeed[3] = 0.0f;      // �� ��° �ؽ�ó Z ��ȯ �ӵ�.

	// �ؽ�ó ��ȯ ���� �ʱ�ȭ�մϴ�.
	m_textureTranslation[0] = 0.0f;
	m_textureTranslation[1] = 0.0f;
	m_textureTranslation[2] = 0.0f;
	m_textureTranslation[3] = 0.0f;

	// �ϴ� ����� ����ϴ�.
	bool result = InitializeSkyPlane(skyPlaneResolution, skyPlaneWidth, skyPlaneTop, skyPlaneBottom, textureRepeat);
	if(!result)
	{
		return false;
	}

	// �ϴ� ��鿡 ���� ���� �� �ε��� ���۸� ����ϴ�.
	result = InitializeBuffers(device, skyPlaneResolution);
	if(!result)
	{
		return false;
	}

	// �ϴ� ��� �ؽ�ó�� �ε��մϴ�.
	result = LoadTextures(device, textureFilename1, textureFilename2);
	if(!result)
	{
		return false;
	}

	return true;
}


void SkyPlaneClass::Shutdown()
{
	// �ϴ� ��� �ؽ�ó�� �����մϴ�.
	ReleaseTextures();

	// �ϴ� ��� �������� ��� �� ���� �� �ε��� ���۸� �����մϴ�.
	ShutdownBuffers();

	// �ϴ� ��� �迭�� �����մϴ�.
	ShutdownSkyPlane();
}


void SkyPlaneClass::Render(ID3D11DeviceContext* deviceContext)
{
	// �ϴ� ����� �������մϴ�.
	RenderBuffers(deviceContext);
}


void SkyPlaneClass::Frame()
{
	// �����̴� ������ �ùķ���Ʈ�ϱ� ���� ��ȯ ���� ������ŵ�ϴ�.
	m_textureTranslation[0] += m_translationSpeed[0];
	m_textureTranslation[1] += m_translationSpeed[1];
	m_textureTranslation[2] += m_translationSpeed[2];
	m_textureTranslation[3] += m_translationSpeed[3];

	// ���� 0���� 1 ������ �����մϴ�.
	if(m_textureTranslation[0] > 1.0f)  {  m_textureTranslation[0] -= 1.0f;  }
	if(m_textureTranslation[1] > 1.0f)  {  m_textureTranslation[1] -= 1.0f;  }
	if(m_textureTranslation[2] > 1.0f)  {  m_textureTranslation[2] -= 1.0f;  }
	if(m_textureTranslation[3] > 1.0f)  {  m_textureTranslation[3] -= 1.0f;  }
}


int SkyPlaneClass::GetIndexCount()
{
	return m_indexCount;
}


ID3D11ShaderResourceView* SkyPlaneClass::GetCloudTexture1()
{
	return m_CloudTexture1->GetTexture();
}


ID3D11ShaderResourceView* SkyPlaneClass::GetCloudTexture2()
{
	return m_CloudTexture2->GetTexture();
}


void SkyPlaneClass::SetBrightness(float brightness)
{
	m_brightness = brightness;
}

float SkyPlaneClass::GetBrightness()
{
	return m_brightness;
}


float SkyPlaneClass::GetTranslation(int index)
{
	return m_textureTranslation[index];
}


bool SkyPlaneClass::InitializeSkyPlane(int skyPlaneResolution, float skyPlaneWidth, float skyPlaneTop, float skyPlaneBottom, int textureRepeat)
{
	float positionX = 0.0f;
	float positionY = 0.0f;
	float positionZ = 0.0f;
	float tu = 0.0f;
	float tv = 0.0f;

	// �ϴ� ��� ��ǥ�� ���� �� �迭�� ����ϴ�.
	m_skyPlane = new SkyPlaneType[(skyPlaneResolution + 1) * (skyPlaneResolution + 1)];
	if(!m_skyPlane)
	{
		return false;
	}

	// �ϴ� ��鿡�� �� ������ ũ�⸦ �����մϴ�.
	float quadSize = skyPlaneWidth / (float)skyPlaneResolution;

	// �ʺ� �������� �ϴ� ����� �������� ����մϴ�.
	float radius = skyPlaneWidth / 2.0f;

	// ���� �� ���� ����� ����մϴ�.
	float constant = (skyPlaneTop - skyPlaneBottom) / (radius * radius);

	// �ؽ�ó ��ǥ ���� ���� ����մϴ�.
	float textureDelta = (float)textureRepeat / (float)skyPlaneResolution;

	// �ϴ� ����� �ݺ��ϰ� ������ ���� ���� ������� ��ǥ�� ����ϴ�.
	for(int j=0; j<=skyPlaneResolution; j++)
	{
		for(int i=0; i<=skyPlaneResolution; i++)
		{
			// ���� ��ǥ�� ����մϴ�.
			positionX = (-0.5f * skyPlaneWidth) + ((float)i * quadSize);
			positionZ = (-0.5f * skyPlaneWidth) + ((float)j * quadSize);
			positionY = skyPlaneTop - (constant * ((positionX * positionX) + (positionZ * positionZ)));

			// �ؽ�ó ��ǥ�� ����մϴ�.
			tu = (float)i * textureDelta;
			tv = (float)j * textureDelta;

			// �� ��ǥ�� �߰��ϱ� ���� �ϴ� ��� �迭�� �ε����� ����մϴ�.
			int index = j * (skyPlaneResolution + 1) + i;

			// �ϴ� ��� �迭�� ��ǥ�� �߰��մϴ�.
			m_skyPlane[index].x = positionX;
			m_skyPlane[index].y = positionY;
			m_skyPlane[index].z = positionZ;
			m_skyPlane[index].tu = tu;
			m_skyPlane[index].tv = tv;
		}
	}

	return true;
}


void SkyPlaneClass::ShutdownSkyPlane()
{
	// �ϴ� ��� �迭�� �����մϴ�.
	if(m_skyPlane)
	{
		delete [] m_skyPlane;
		m_skyPlane = 0;
	}
}


bool SkyPlaneClass::InitializeBuffers(ID3D11Device* device, int skyPlaneResolution)
{
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	int index4 = 0;

	// �ϴ� ��� �޽��� ���� ���� ����մϴ�.
	m_vertexCount = (skyPlaneResolution + 1) * (skyPlaneResolution + 1) * 6;

	// �ε��� ���� ������ ���� ���� �����մϴ�.
	m_indexCount = m_vertexCount;
		
	// ���� �迭�� ����ϴ�.
	VertexType* vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// �ε��� �迭�� ����ϴ�.
	unsigned long* indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// �ε����� ���� �迭�� �ʱ�ȭ �մϴ�.
	int index = 0;

	// �ϴ� ��� �迭 �����ͷ� �������� �ε��� �迭�� �ε��մϴ�.
	for(int j=0; j<skyPlaneResolution; j++)
	{
		for(int i=0; i<skyPlaneResolution; i++)
		{
			index1 = j * (skyPlaneResolution + 1) + i;
			index2 = j * (skyPlaneResolution + 1) + (i+1);
			index3 = (j+1) * (skyPlaneResolution + 1) + i;
			index4 = (j+1) * (skyPlaneResolution + 1) + (i+1);

			// �ﰢ�� 1 - ���� ��
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index1].x, m_skyPlane[index1].y, m_skyPlane[index1].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index1].tu, m_skyPlane[index1].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 1 - ������ ��
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index2].x, m_skyPlane[index2].y, m_skyPlane[index2].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index2].tu, m_skyPlane[index2].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 1 - ���� �Ʒ�
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index3].x, m_skyPlane[index3].y, m_skyPlane[index3].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index3].tu, m_skyPlane[index3].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 2 - ���� �Ʒ�
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index3].x, m_skyPlane[index3].y, m_skyPlane[index3].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index3].tu, m_skyPlane[index3].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 2 - ������ ��
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index2].x, m_skyPlane[index2].y, m_skyPlane[index2].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index2].tu, m_skyPlane[index2].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 2 - ������ �Ʒ�
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index4].x, m_skyPlane[index4].y, m_skyPlane[index4].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index4].tu, m_skyPlane[index4].tv);
			indices[index] = index;
			index++;
		}
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

	// ���� ���۸� ����ϴ�.
	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
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
	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	// ���ؽ��� �ε��� ���۰� �����ǰ� �ε�� �迭�� �����մϴ�.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void SkyPlaneClass::ShutdownBuffers()
{
	// �ε��� ���۸� �����մϴ�.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// ���ؽ� ���۸� �����մϴ�.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void SkyPlaneClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
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


bool SkyPlaneClass::LoadTextures(ID3D11Device* device, const WCHAR* textureFilename1, const WCHAR* textureFilename2)
{
	// ù ��° Ŭ���� �ؽ�ó ��ü�� ����ϴ�.
	m_CloudTexture1 = new TextureClass;
	if(!m_CloudTexture1)
	{
		return false;
	}

	// ù ��° ���� �ؽ�ó ��ü�� �ʱ�ȭ�մϴ�.
	if(!m_CloudTexture1->Initialize(device, const_cast<WCHAR*>(textureFilename1)))
	{
		return false;
	}

	// �� ��° Ŭ���� �ؽ�ó ��ü�� ����ϴ�.
	m_CloudTexture2 = new TextureClass;
	if(!m_CloudTexture2)
	{
		return false;
	}

	// �� ��° ���� �ؽ�ó ��ü�� �ʱ�ȭ�մϴ�.
	if(!m_CloudTexture2->Initialize(device, const_cast<WCHAR*>(textureFilename2)))
	{
		return false;
	}

	return true;
}


void SkyPlaneClass::ReleaseTextures()
{
	// �ؽ�ó ��ü�� �����մϴ�.
	if(m_CloudTexture1)
	{
		m_CloudTexture1->Shutdown();
		delete m_CloudTexture1;
		m_CloudTexture1 = 0;
	}

	if(m_CloudTexture2)
	{
		m_CloudTexture2->Shutdown();
		delete m_CloudTexture2;
		m_CloudTexture2 = 0;
	}
}