#version 330 core

layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	vec4 texColor = fs_in.color;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = fs_in.color * texture(textures[tid], fs_in.uv);
	}
	color = texColor;
}