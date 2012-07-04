/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  DepthFBO.h, created by Marek Bereza on 19/04/2012.
 */


class DepthFBO {
	
public:
	DepthFBO() {
		allocated = false;
	}
	~DepthFBO() {
		if(allocated) {
			glDeleteFramebuffers(1, &buffId);
		}
	}
	
	void allocate(int width, int height) {
		allocated = true;
		glEnable (GL_DEPTH_TEST);
		glGenFramebuffers(1, &buffId);
		begin();
		
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		
		tex.texData.bFlipTexture = true;
		tex.allocate(1024, 1024, GL_DEPTH_COMPONENT, false /* forces GL_TEXTURE_2D */);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tex.texData.textureTarget, tex.texData.textureID, 0);
		
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE );
		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );	
		
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch(status) {
			case GL_FRAMEBUFFER_COMPLETE:
				ofLog(OF_LOG_ERROR, "FRAMEBUFFER_COMPLETE - OK");
				break;
			default:
				ofLog(OF_LOG_ERROR, "FRAMEBUFFER ERROR!\n");
				break;
		}
		end();
	}
	
	ofTexture &getTextureReference() {
		return tex;
	}
	void begin() {
		glBindFramebuffer(GL_FRAMEBUFFER, buffId);
	}
	
	void end() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void draw(float x, float y, float width, float height) {
		tex.draw(x, y, width, height);
	}
	void draw(float x, float y) {
		tex.draw(x, y);
	}
	
private:
	ofTexture tex;
	GLuint buffId;
	bool allocated;
};
