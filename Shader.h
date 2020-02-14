#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>

#include <string>
#include <vector>

namespace Engine
{
    class Shader
    {
    public:
        Shader();
        ~Shader();

        void load( const std::string& vertexPath, const std::string& fragmentPath );

        void bind() const;

        GLuint getID() const;

    private:
        GLuint progID;
    };
}

#endif // SHADER_H
