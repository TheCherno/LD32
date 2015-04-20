precision highp float;

uniform highp vec4 colour;
uniform highp vec2 light_pos;

varying highp vec4 vs_position;
varying highp vec2 vs_uv;
varying highp float vs_tid;
varying highp vec4 vs_color;

uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform sampler2D texture_3;
uniform sampler2D texture_4;
uniform sampler2D texture_5;
uniform sampler2D texture_6;
uniform sampler2D texture_7;

uniform vec2 nuke_pos;
uniform highp float nuke_intensity;
uniform highp float fade_out;

void main()
{
	float intensity = 200.0 / length(vs_position.xy - vec2(880, 1020)) + 0.2;
	vec4 sunColor = vec4(1, 0.9, 0.8, 1) * intensity;
	vec4 texColor = vs_color;

	float nukeIntensity = nuke_intensity / length(vs_position.xy - nuke_pos);
	vec4 nuke = vec4(1, 0.8, 0.8, 1) * nukeIntensity;

	if (vs_tid > 0.0)
	{
		int tid = int(vs_tid - 0.5);
		if (tid == 0)
			texColor = vs_color * texture2D(texture_0, vs_uv);
		else if (tid == 1)
			texColor = vs_color * texture2D(texture_1, vs_uv);
		else if (tid == 2)
			texColor = vs_color * texture2D(texture_2, vs_uv);
		else if (tid == 3)
			texColor = vs_color * texture2D(texture_3, vs_uv);
		else if (tid == 4)
			texColor = vs_color * texture2D(texture_4, vs_uv);
		else if (tid == 5)
			texColor = vs_color * texture2D(texture_5, vs_uv);
		else if (tid == 6)
			texColor = vs_color * texture2D(texture_6, vs_uv);
		else if (tid == 7)
			texColor = vs_color * texture2D(texture_7, vs_uv);
	}
	gl_FragColor = texColor * sunColor * fade_out;

	if (nuke_pos.x > 0.0)
		gl_FragColor *= nuke;

	gl_FragColor.a = texColor.a;
}