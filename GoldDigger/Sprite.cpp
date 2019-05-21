#include "GoldDiggerPCH.h"
#include "Sprite.h"
#include "structs.h"
#include "ResourceManager.h"

void GD::Sprite::Initialize()
{
	m_Texture->SDLTexture = ResourceManager::GetInstance().GetTexture(m_Name);
}

void GD::Sprite::Update(float deltaTime)
{

}
