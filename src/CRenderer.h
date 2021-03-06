#ifndef COPENGLDRIVER_H
#define COPENGLDRIVER_H

#include "CCamera.h"
#include "CException.h"

class CInputHandler;
struct SMaterial;

class CRenderer
{
    public:
        CRenderer(unsigned w, unsigned h);
        virtual ~CRenderer();
        void run();
        void setTitle(const char *pszTitle);
        void setModelTransform(const glm::mat4 &ModelMat, bool bSkybox = false);
        void setTexture(GLuint Texture);
        void clear(const glm::vec3 &Color = glm::vec3(0.0f, 0.0f, 0.0f));
        
        void setLightPos(const glm::vec3 &Position)
        {
            m_LightPos = Position;
        }
        
        void setLightColor(const glm::vec3 &Color)
        {
            m_LightClr = Color;
        }

        void setViewMatrix(const glm::mat4 &View)
        {
            m_ViewMatrix = View;
        }
        
        void setProjMatrix(const glm::mat4 &Proj)
        {
            m_ProjMatrix = Proj;
        }

        bool isClosed() const
        {
            return m_bClosed;
        }
        
        void close()
        {
            glfwSetWindowShouldClose(m_pWnd, 1);
        }

        int getWidth() const
        {
            return m_Width;
        }

        int getHeight() const
        {
            return m_Height;
        }

        bool isVisible() const
        {
            return (glfwGetWindowAttrib(m_pWnd, GLFW_VISIBLE) != 0 &&
                glfwGetWindowAttrib(m_pWnd, GLFW_ICONIFIED) == 0);
        }
        
        GLuint setProgram(GLuint Program);
        
        GLuint getProgram()
        {
            return m_Program;
        }
        
        void setProgramUniform(const char *pszName, int Value);
        void setProgramUniform(const char *pszName, float Value);
        void setProgramUniform(const char *pszName, const glm::vec2 &Value);
        void setProgramUniform(const char *pszName, const glm::vec3 &Value);
        void setProgramUniform(const char *pszName, const glm::vec4 &Value);
        void setInputHandler(CInputHandler *pHandler);
        void setDoubleSided(bool DoubleSided);
        void setMaterial(const SMaterial &Mat);
        
        void toggleWireframe()
        {
            m_bWireframe = !m_bWireframe;
        }

    private:
        GLFWwindow *m_pWnd;
        int m_Width, m_Height;
        bool m_bClosed, m_bWireframe;
        
        CInputHandler *m_pInputHandler;
        GLuint m_Program;
        glm::mat4 m_ViewMatrix, m_ProjMatrix;
        
        glm::vec3 m_LightPos, m_LightClr;
        
        static void glfwErrorCallback(int iErrorNum, const char *pszDescription);
        static void onKey(GLFWwindow *pWindow, int Key, int Scancode, int Action, int Mods);
        static void onFramebufferSize(GLFWwindow *pWindow, int Width, int Height);
        void handleCursorMove();
};

DEFINE_EXCEPTION_CLASS(COpenGLException);

#endif // COPENGLDRIVER_H
