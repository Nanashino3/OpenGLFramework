#version 460 core

// �}�e���A�����
struct Material
{
	vec3 mAmbient;	// �����ˌW��(Ka)
	vec3 mDiffuse;	// �g�U���ˌW��(Kd)
};
uniform Material uMaterial;

// ���s����
struct DirectionalLight
{
	vec3 mDirection;	// �����̌���
	vec3 mDiffuseColor;	// �����̊g�U��
};
uniform DirectionalLight uDirLight;

// �e�N�X�`���̃T���v�����O
uniform sampler2D uTexture;
// �Q�[���̊���ݒ�
uniform vec3 uAmbientColor;

in vec2 fragTexCoord;	// �e�N�X�`�����W
in vec3 fragNormal;		// �@�����W
out vec4 outColor;

// �e������̌v�Z���s��
vec3 CalcAmbientColor();
vec3 CalcDiffuseColor();

void main()
{
	vec3 ambientColor = CalcAmbientColor();
	vec3 diffuseColor = CalcDiffuseColor();

	// ���� + �g�U���ˌ�
	vec3 lambert = ambientColor + diffuseColor;
	outColor = texture(uTexture, fragTexCoord) * vec4(lambert, 1.0);
}

// �����v�Z
vec3 CalcAmbientColor()
{	
	return uMaterial.mAmbient * uAmbientColor;
}

// �g�U���v�Z
vec3 CalcDiffuseColor()
{
	vec3 diffuse = vec3(0, 0, 0);

	// ���K�����Ă���
	vec3 N = normalize(fragNormal);				// �@���x�N�g��
	vec3 L = normalize(-uDirLight.mDirection);	// �\�ʂ�������ւ̃x�N�g��

	// N��L�̓��ς����߂�
	float NdotL = dot(N, L);

	if(NdotL > 0){
		// �����ˌ�(Ka) * (N�EL) * �����ɐݒ肳�ꂽ��
		diffuse = uMaterial.mDiffuse * NdotL * uDirLight.mDiffuseColor;
	}

	return diffuse;
}