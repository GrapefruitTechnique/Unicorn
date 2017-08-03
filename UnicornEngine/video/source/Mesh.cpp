/*
* Copyright (C) 2017 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <unicorn/video/Mesh.hpp>

namespace unicorn
{
namespace video
{
Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices, const std::list<Texture*>& textures)
{
    SetMeshData(vertices, indices);
    AddTextures(textures);
}

Mesh::~Mesh()
{
}

void Mesh::SetMeshData(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
{
    m_vertices = vertices;
    m_indices = indices;
}

const std::vector<Vertex>& Mesh::GetVertices() const
{
    return m_vertices;
}

const std::vector<uint16_t>& Mesh::GetIndices() const
{
    return m_indices;
}

std::list<Texture*> const& Mesh::GetTextures() const
{
    return m_textures;
}

void Mesh::AddTexture(Texture* texture)
{
    m_textures.push_back(texture);
}

void Mesh::AddTextures(const std::list<Texture*>& textures)
{
    m_textures.insert(textures.end(), textures.begin(), textures.end());
}

Vertex::Vertex(glm::vec3 pos) : pos(pos)
{
}
}
}
