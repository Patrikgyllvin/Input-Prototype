#include "Shader.h"

namespace Engine
{
    Shader::Shader()
    :
    progID( 0 )
    {}

    Shader::~Shader()
    {
        glDeleteProgram( this->progID );
    }

    void Shader::load( const std::string& vertexPath, const std::string& fragmentPath )
    {
        GLuint vertID = glCreateShader( GL_VERTEX_SHADER );
        GLuint fragID = glCreateShader( GL_FRAGMENT_SHADER );

        std::string vertexSource;
        std::ifstream vertexStream( vertexPath.c_str() );

        if( vertexStream.is_open() )
        {
            std::stringstream buff;
            buff << vertexStream.rdbuf();
            vertexSource = buff.str();
        }
        else
        {
            fprintf( stderr, "Could not find vertex shader: %s\n", vertexPath.c_str() );
            return;
        }

        std::string fragSource;
        std::ifstream fragmentStream( fragmentPath.c_str() );

        if( fragmentStream.is_open() )
        {
            std::stringstream buff;
            buff << fragmentStream.rdbuf();
            fragSource = buff.str();
        }
        else
        {
            fprintf( stderr, "Could not find fragment shader: %s\n", fragmentPath.c_str() );
            return;
        }

        int infoLogLength;
        GLint compiled = GL_FALSE;

        fprintf( stdout, "Compiling vertex shader..." );

        // Vertex Shader

        const char* vertexPointer = vertexSource.c_str();
        glShaderSource( vertID, 1, &vertexPointer, NULL );
        glCompileShader( vertID );

        glGetShaderiv( vertID, GL_COMPILE_STATUS, &compiled );

		if (!compiled)
		{
			glGetShaderiv( vertID, GL_INFO_LOG_LENGTH, &infoLogLength );
			std::string vertShaderLog( infoLogLength, ' ' );
			glGetShaderInfoLog( vertID, infoLogLength, &infoLogLength, &vertShaderLog[0] );
			fprintf( stderr, "\n\n%s\n", &vertShaderLog[0] );
		}
		else
			fprintf( stdout, " success!\n" );

        fprintf( stdout, "Compiling fragment shader... " );

        // Fragment Shader

        const char* fragPointer = fragSource.c_str();
        glShaderSource( fragID, 1, &fragPointer, NULL );
        glCompileShader( fragID );

        glGetShaderiv( fragID, GL_COMPILE_STATUS, &compiled );

		if( !compiled )
		{
			glGetShaderiv( fragID, GL_INFO_LOG_LENGTH, &infoLogLength );
			std::string fragShaderLog( infoLogLength, ' ' );
			glGetShaderInfoLog( fragID, infoLogLength, NULL, &fragShaderLog[0] );
			fprintf( stderr, "\n\n%s\n", &fragShaderLog[0] );
		}
		else
			fprintf(stdout, " success!\n" );

        fprintf( stdout, "\nLinking program... " );

        GLuint tmpProgID = glCreateProgram();
        glAttachShader( tmpProgID, vertID );
        glAttachShader( tmpProgID, fragID );
        glLinkProgram( tmpProgID );

        glGetProgramiv( tmpProgID, GL_INFO_LOG_LENGTH, &infoLogLength );

		if( !compiled )
		{
			glGetProgramiv( tmpProgID, GL_LINK_STATUS, &compiled );
			std::string progLog( infoLogLength, ' ' );
			glGetProgramInfoLog( tmpProgID, infoLogLength, &infoLogLength, &progLog[ 0 ] );
			fprintf( stdout, "\n\n%s\n", &progLog[ 0 ] );
		}
		else
			fprintf( stderr, " success!\n" );

        glDeleteShader( vertID );
        glDeleteShader( fragID );

        this->progID = tmpProgID;
    }

    void Shader::bind() const
    {
        glUseProgram( this->progID );
    }

    GLuint Shader::getID() const
    {
        return this->progID;
    }
}
