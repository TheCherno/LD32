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
uniform vec2 nuke_pos;
uniform float nuke_intensity;
uniform float fade_out;

void main()
{
	float intensity = 200.0 / length(fs_in.position.xy - vec2(880, 1020)) + 0.1;
	vec4 sunColor = vec4(1, 0.9, 0.8, 1) * intensity;
	vec4 texColor = fs_in.color;

	float nukeIntensity = nuke_intensity / length(fs_in.position.xy - nuke_pos);
	vec4 nuke = vec4(1, 0.8, 0.8, 1) * nukeIntensity;

	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = fs_in.color * texture(textures[tid], fs_in.uv);
	}
	color = texColor * sunColor * fade_out;

	if (nuke_pos.x != 0)
		color *= nuke;

	color.a = texColor.a;
}