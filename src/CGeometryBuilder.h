#ifndef CGEOMETRYBUILDER_H
#define CGEOMETRYBUILDER_H

#include "SVertex.h"
#include "CMesh.h"

class CMesh;

class CGeometryBuilder
{
    public:
        CGeometryBuilder();
        void addQuad(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const glm::vec3 &v4);
        void addIcosphere(unsigned n = 0);
        void addCylinder(float Radius, bool Inside = false, unsigned Segments = 8);
        void addTube(float RadiusIn = 1.0f, float RadiusOut = 2.0f, unsigned Segments = 8);
        void addTorus(float Radius, float CircleRadius, unsigned Segments = 8, unsigned CircleSegments = 8);
        void addVertices(const std::vector<SVertex> &Vertices, const std::vector<uint16_t> &Indices);
        void addBox();
        void addBox(const glm::vec3 Vertices[8]);
        void addPolygon(const glm::vec3 Vertices[], unsigned Count);
        void addPolygon(const glm::vec3 Vertices[], unsigned VertCount, const uint16_t Indices[], unsigned IndCount);
        CMesh::SOffsetSize subMesh();
        CMesh *createMesh(bool bDebug = false);
        void switchVerticesOrder();
        
        void removeAllVertices()
        {
            m_Vertices.clear();
            m_Indices.clear();
        }
        
        uint32_t getColor() const
        {
            return m_Color;
        }
        
        uint32_t setColor(uint32_t Color)
        {
            uint32_t Ret = m_Color;
            m_Color = Color;
            return Ret;
        }
        
        const std::vector<SVertex> &getVertices() const
        {
            return m_Vertices;
        }
        
        const std::vector<uint16_t> &getIndices() const
        {
            return m_Indices;
        }
        
        void setTransform(const glm::mat4 &Transform)
        {
            m_Transform = Transform;
            m_TransformNormal = glm::mat3(Transform);
        }
    
    private:
        std::vector<SVertex> m_Vertices;
        std::vector<uint16_t> m_Indices;
        glm::mat4 m_Transform;
        glm::mat3 m_TransformNormal;
        unsigned m_Offset;
        uint32_t m_Color;
        
        glm::vec3 transformVec3(const glm::vec3 &v)
        {
            return glm::vec3(m_Transform * glm::vec4(v, 1.0f));
        }
        
        glm::vec3 transformVec3(float x, float y, float z)
        {
            return glm::vec3(m_Transform * glm::vec4(x, y, z, 1.0f));
        }
        
        void addFace(unsigned Offset, unsigned Index1, unsigned Index2, unsigned Index3);
        unsigned addSphereVertex(const glm::vec3 &Pos);
        unsigned getIcosphereMiddlePoint(unsigned Index1, unsigned Index2, std::unordered_map<unsigned, unsigned> &MiddlePoints);
};

#endif // CGEOMETRYBUILDER_H
