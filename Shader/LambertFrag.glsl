#version 460 core

// マテリアル情報
struct Material
{
	vec3 mAmbient;	// 環境反射係数(Ka)
	vec3 mDiffuse;	// 拡散反射係数(Kd)
};
uniform Material uMaterial;

// 平行光源
struct DirectionalLight
{
	vec3 mDirection;	// 光源の向き
	vec3 mDiffuseColor;	// 光源の拡散光
};
uniform DirectionalLight uDirLight;

// テクスチャのサンプリング
uniform sampler2D uTexture;
// ゲームの環境を設定
uniform vec3 uAmbientColor;

in vec2 fragTexCoord;	// テクスチャ座標
in vec3 fragNormal;		// 法線座標
out vec4 outColor;

// 各種光源の計算を行う
vec3 CalcAmbientColor();
vec3 CalcDiffuseColor();

void main()
{
	vec3 ambientColor = CalcAmbientColor();
	vec3 diffuseColor = CalcDiffuseColor();

	// 環境光 + 拡散反射光
	vec3 lambert = ambientColor + diffuseColor;
	outColor = texture(uTexture, fragTexCoord) * vec4(lambert, 1.0);
}

// 環境光計算
vec3 CalcAmbientColor()
{	
	return uMaterial.mAmbient * uAmbientColor;
}

// 拡散光計算
vec3 CalcDiffuseColor()
{
	vec3 diffuse = vec3(0, 0, 0);

	// 正規化しておく
	vec3 N = normalize(fragNormal);				// 法線ベクトル
	vec3 L = normalize(-uDirLight.mDirection);	// 表面から光源へのベクトル

	// NとLの内積を求める
	float NdotL = dot(N, L);

	if(NdotL > 0){
		// 環境反射光(Ka) * (N・L) * 光源に設定された光
		diffuse = uMaterial.mDiffuse * NdotL * uDirLight.mDiffuseColor;
	}

	return diffuse;
}