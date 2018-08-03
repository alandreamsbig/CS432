#pragma once
#include "Drawable.h"
class treeTop : //derived from drawable class
	public Drawable
{
public:
	void cleanup();
	void initOffsets();
	void setOffsets(vec4 newOffsets[]);
	void setNumTrees(int num);
	void initColors();
	void initTexCoords();
	void applyTransformation(mat4 input);
	
	//constructor
	treeTop();
	//destructor
	~treeTop();


	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc;
	GLuint vPosition_loc;
	GLuint vColor_loc, vTexCoord_loc;
	GLuint treeOffset_Loc;
	GLuint buffer;
	void draw();

	int numTrees = 4096;
	mat4 model_matrix;
	int numSnowflakes = 4096 * 2;
	vec4 treeOffsets[4096 * 2];
	vec4 vertexColors[690];

	GLuint texture;

	std::string currentTextureName = "branches.ppm";

	vec2 textureCoords[690];



	vec4 fullVertices[690] = {
		vec4(0.019167,5.147034,0.022685,1.0),
		vec4(0.199847,4.386368,-0.186952,1.0),
		vec4(0.015674,4.386367,-0.253986,1.0),
		vec4(0.199847,4.386368,-0.186952,1.0),
		vec4(0.033842,5.147034,0.034998,1.0),
		vec4(0.292234,4.323041,-0.023413,1.0),
		vec4(0.033842,5.147034,0.034998,1.0),
		vec4(0.263809,4.386367,0.175798,1.0),
		vec4(0.292234,4.323041,-0.023413,1.0),
		vec4(0.032072,5.147034,0.045036,1.0),
		vec4(0.113670,4.386367,0.301780,1.0),
		vec4(0.263809,4.386367,0.175798,1.0),
		vec4(0.113670,4.386367,0.301780,1.0),
		vec4(0.014070,5.147034,0.051588,1.0),
		vec4(-0.087932,4.323041,0.295584,1.0),
		vec4(0.014070,5.147034,0.051588,1.0),
		vec4(-0.232462,4.386367,0.175798,1.0),
		vec4(-0.087932,4.323041,0.295584,1.0),
		vec4(-0.232462,4.386367,0.175798,1.0),
		vec4(0.004492,5.147034,0.034998,1.0),
		vec4(-0.266496,4.386367,-0.017217,1.0),
		vec4(0.019167,5.147034,0.022685,1.0),
		vec4(0.024263,5.147034,0.051588,1.0),
		vec4(0.032072,5.147034,0.045036,1.0),
		vec4(0.009589,5.147034,0.026171,1.0),
		vec4(0.015674,4.386367,-0.253986,1.0),
		vec4(-0.174109,4.323041,-0.193148,1.0),
		vec4(-0.266496,4.386367,-0.017217,1.0),
		vec4(0.009589,5.147034,0.026171,1.0),
		vec4(-0.174109,4.323041,-0.193148,1.0),
		vec4(0.979368,0.916480,-0.113076,1.0),
		vec4(-0.353069,1.047231,0.994068,1.0),
		vec4(-0.005440,1.110557,-0.939428,1.0),
		vec4(-1.162461,0.865147,-0.150182,1.0),
		vec4(-0.569643,1.403287,-0.618026,1.0),
		vec4(-0.766733,0.801821,-0.851516,1.0),
		vec4(-0.569643,1.403287,-0.618026,1.0),
		vec4(-0.006855,0.865147,-1.119851,1.0),
		vec4(-0.766733,0.801821,-0.851516,1.0),
		vec4(-1.023078,0.865147,0.640299,1.0),
		vec4(-0.862932,1.466613,-0.094124,1.0),
		vec4(-1.162461,0.865147,-0.150182,1.0),
		vec4(-0.306797,1.403287,0.872648,1.0),
		vec4(-1.023078,0.865147,0.640299,1.0),
		vec4(-0.413802,0.801821,1.150053,1.0),
		vec4(0.394483,0.865147,1.156250,1.0),
		vec4(-0.306797,1.403287,0.872648,1.0),
		vec4(-0.413802,0.801821,1.150053,1.0),
		vec4(1.009368,0.865147,0.640300,1.0),
		vec4(0.296607,1.466613,0.878845,1.0),
		vec4(0.394483,0.865147,1.156250,1.0),
		vec4(0.858351,1.466613,-0.094124,1.0),
		vec4(1.009368,0.865147,0.640300,1.0),
		vec4(1.143143,0.801821,-0.156378,1.0),
		vec4(0.747414,0.865147,-0.845319,1.0),
		vec4(0.858351,1.466613,-0.094124,1.0),
		vec4(1.143143,0.801821,-0.156378,1.0),
		vec4(-0.002290,1.466613,-0.816288,1.0),
		vec4(0.747414,0.865147,-0.845319,1.0),
		vec4(-0.006855,0.865147,-1.119851,1.0),
		vec4(-0.470645,3.612862,-0.047718,1.0),
		vec4(-0.106769,4.373131,-0.103204,1.0),
		vec4(-0.309076,3.549535,-0.343475,1.0),
		vec4(-0.106769,4.373131,-0.103204,1.0),
		vec4(0.010725,3.612862,-0.451635,1.0),
		vec4(-0.309076,3.549535,-0.343475,1.0),
		vec4(-0.412585,3.612862,0.281558,1.0),
		vec4(-0.162981,4.436458,0.010068,1.0),
		vec4(-0.470645,3.612862,-0.047718,1.0),
		vec4(-0.052405,4.373131,0.205109,1.0),
		vec4(-0.412585,3.612862,0.281558,1.0),
		vec4(-0.162062,3.549536,0.490282,1.0),
		vec4(0.177903,3.612862,0.496478,1.0),
		vec4(-0.052405,4.373131,0.205109,1.0),
		vec4(-0.162062,3.549536,0.490282,1.0),
		vec4(0.434034,3.612862,0.281558,1.0),
		vec4(0.076845,4.436458,0.211305,1.0),
		vec4(0.177903,3.612862,0.496478,1.0),
		vec4(0.193029,4.436458,0.010068,1.0),
		vec4(0.434034,3.612862,0.281558,1.0),
		vec4(0.486486,3.549535,-0.053915,1.0),
		vec4(0.324917,3.612862,-0.337279,1.0),
		vec4(0.193029,4.436458,0.010068,1.0),
		vec4(0.486486,3.549535,-0.053915,1.0),
		vec4(0.015024,4.436458,-0.139296,1.0),
		vec4(0.324917,3.612862,-0.337279,1.0),
		vec4(0.010725,3.612862,-0.451635,1.0),
		vec4(0.010529,3.665409,-0.315061,1.0),
		vec4(0.463775,2.762699,-0.504165,1.0),
		vec4(0.005286,2.762699,-0.671042,1.0),
		vec4(0.463775,2.762699,-0.504165,1.0),
		vec4(0.365764,3.665409,-0.016983,1.0),
		vec4(0.702124,2.699372,-0.087815,1.0),
		vec4(0.365764,3.665409,-0.016983,1.0),
		vec4(0.623007,2.762699,0.398883,1.0),
		vec4(0.702124,2.699372,-0.087815,1.0),
		vec4(0.623007,2.762699,0.398883,1.0),
		vec4(0.133901,3.665409,0.384616,1.0),
		vec4(0.249243,2.762699,0.712509,1.0),
		vec4(0.249243,2.762699,0.712509,1.0),
		vec4(-0.118452,3.602083,0.378420,1.0),
		vec4(-0.244281,2.699373,0.706312,1.0),
		vec4(-0.118452,3.602083,0.378420,1.0),
		vec4(-0.612436,2.762699,0.398883,1.0),
		vec4(-0.244281,2.699373,0.706312,1.0),
		vec4(-0.612436,2.762699,0.398883,1.0),
		vec4(-0.344706,3.665409,-0.016983,1.0),
		vec4(-0.697161,2.762699,-0.081619,1.0),
		vec4(-0.226943,3.602082,-0.236866,1.0),
		vec4(0.005286,2.762699,-0.671042,1.0),
		vec4(-0.458813,2.699373,-0.510362,1.0),
		vec4(-0.697161,2.762699,-0.081619,1.0),
		vec4(-0.226943,3.602082,-0.236866,1.0),
		vec4(-0.458813,2.699373,-0.510362,1.0),
		vec4(-0.864248,1.998844,-0.105654,1.0),
		vec4(-0.359524,2.751434,-0.384325,1.0),
		vec4(-0.569569,1.935518,-0.631965,1.0),
		vec4(-0.359524,2.751434,-0.384325,1.0),
		vec4(0.000399,1.998844,-0.831178,1.0),
		vec4(-0.569569,1.935518,-0.631965,1.0),
		vec4(-0.759959,1.998845,0.485799,1.0),
		vec4(-0.545192,2.814761,-0.046827,1.0),
		vec4(-0.864248,1.998844,-0.105654,1.0),
		vec4(-0.191317,2.751434,0.569622,1.0),
		vec4(-0.759959,1.998845,0.485799,1.0),
		vec4(-0.305499,1.935518,0.865646,1.0),
		vec4(0.300687,1.998845,0.871843,1.0),
		vec4(-0.191317,2.751434,0.569622,1.0),
		vec4(-0.305499,1.935518,0.865646,1.0),
		vec4(0.760756,1.998844,0.485799,1.0),
		vec4(0.196847,2.814761,0.575818,1.0),
		vec4(0.300687,1.998845,0.871843,1.0),
		vec4(0.556331,2.814761,-0.046827,1.0),
		vec4(0.760756,1.998844,0.485799,1.0),
		vec4(0.859436,1.935518,-0.111850,1.0),
		vec4(0.564756,1.998845,-0.625769,1.0),
		vec4(0.556331,2.814761,-0.046827,1.0),
		vec4(0.859436,1.935518,-0.111850,1.0),
		vec4(0.005569,2.814761,-0.508971,1.0),
		vec4(0.564756,1.998845,-0.625769,1.0),
		vec4(0.000399,1.998844,-0.831178,1.0),
		vec4(0.001149,2.056518,-0.681816,1.0),
		vec4(0.669916,1.407060,-0.752068,1.0),
		vec4(-0.003388,1.407059,-0.997131,1.0),
		vec4(0.669916,1.407060,-0.752068,1.0),
		vec4(0.726197,2.056518,-0.073428,1.0),
		vec4(1.022565,1.343733,-0.137744,1.0),
		vec4(0.726197,2.056518,-0.073428,1.0),
		vec4(0.903752,1.407060,0.574081,1.0),
		vec4(1.022565,1.343733,-0.137744,1.0),
		vec4(0.903752,1.407060,0.574081,1.0),
		vec4(0.252955,2.056519,0.746250,1.0),
		vec4(0.354870,1.407060,1.034648,1.0),
		vec4(0.354870,1.407060,1.034648,1.0),
		vec4(-0.256267,1.993192,0.740054,1.0),
		vec4(-0.367254,1.343733,1.028452,1.0),
		vec4(-0.256267,1.993192,0.740054,1.0),
		vec4(-0.910528,1.407060,0.574081,1.0),
		vec4(-0.367254,1.343733,1.028452,1.0),
		vec4(-0.910528,1.407060,0.574081,1.0),
		vec4(-0.723899,2.056518,-0.073428,1.0),
		vec4(-1.034949,1.407059,-0.131548,1.0),
		vec4(-0.477702,1.993192,-0.515766,1.0),
		vec4(-0.003388,1.407059,-0.997131,1.0),
		vec4(-0.682301,1.343733,-0.758265,1.0),
		vec4(-1.034949,1.407059,-0.131548,1.0),
		vec4(-0.477702,1.993192,-0.515766,1.0),
		vec4(-0.682301,1.343733,-0.758265,1.0),
		vec4(-0.266496,4.386367,-0.017217,1.0),
		vec4(-0.106769,4.373131,-0.103204,1.0),
		vec4(-0.162981,4.436458,0.010068,1.0),
		vec4(-0.106769,4.373131,-0.103204,1.0),
		vec4(0.015674,4.386367,-0.253986,1.0),
		vec4(0.015024,4.436458,-0.139296,1.0),
		vec4(-0.232462,4.386367,0.175798,1.0),
		vec4(-0.162981,4.436458,0.010068,1.0),
		vec4(-0.141511,4.436458,0.131830,1.0),
		vec4(-0.052405,4.373131,0.205109,1.0),
		vec4(-0.232462,4.386367,0.175798,1.0),
		vec4(-0.141511,4.436458,0.131830,1.0),
		vec4(0.113670,4.386367,0.301780,1.0),
		vec4(-0.052405,4.373131,0.205109,1.0),
		vec4(0.076845,4.436458,0.211305,1.0),
		vec4(0.171559,4.436458,0.131830,1.0),
		vec4(0.113670,4.386367,0.301780,1.0),
		vec4(0.076845,4.436458,0.211305,1.0),
		vec4(0.193029,4.436458,0.010068,1.0),
		vec4(0.263809,4.386367,0.175798,1.0),
		vec4(0.171559,4.436458,0.131830,1.0),
		vec4(0.131209,4.436458,-0.097008,1.0),
		vec4(0.292234,4.323041,-0.023413,1.0),
		vec4(0.193029,4.436458,0.010068,1.0),
		vec4(0.015024,4.436458,-0.139296,1.0),
		vec4(0.199847,4.386368,-0.186952,1.0),
		vec4(0.131209,4.436458,-0.097008,1.0),
		vec4(0.010529,3.665409,-0.315061,1.0),
		vec4(0.324917,3.612862,-0.337279,1.0),
		vec4(0.242392,3.665409,-0.230669,1.0),
		vec4(0.242392,3.665409,-0.230669,1.0),
		vec4(0.486486,3.549535,-0.053915,1.0),
		vec4(0.365764,3.665409,-0.016983,1.0),
		vec4(0.365764,3.665409,-0.016983,1.0),
		vec4(0.434034,3.612862,0.281558,1.0),
		vec4(0.322917,3.665409,0.226012,1.0),
		vec4(0.322917,3.665409,0.226012,1.0),
		vec4(0.177903,3.612862,0.496478,1.0),
		vec4(0.133901,3.665409,0.384616,1.0),
		vec4(0.177903,3.612862,0.496478,1.0),
		vec4(-0.118452,3.602083,0.378420,1.0),
		vec4(0.133901,3.665409,0.384616,1.0),
		vec4(-0.118452,3.602083,0.378420,1.0),
		vec4(-0.412585,3.612862,0.281558,1.0),
		vec4(-0.301860,3.665409,0.226012,1.0),
		vec4(-0.412585,3.612862,0.281558,1.0),
		vec4(-0.344706,3.665409,-0.016983,1.0),
		vec4(-0.301860,3.665409,0.226012,1.0),
		vec4(-0.226943,3.602082,-0.236866,1.0),
		vec4(0.010725,3.612862,-0.451635,1.0),
		vec4(0.010529,3.665409,-0.315061,1.0),
		vec4(-0.470645,3.612862,-0.047718,1.0),
		vec4(-0.226943,3.602082,-0.236866,1.0),
		vec4(-0.344706,3.665409,-0.016983,1.0),
		vec4(-0.697161,2.762699,-0.081619,1.0),
		vec4(-0.359524,2.751434,-0.384325,1.0),
		vec4(-0.545192,2.814761,-0.046827,1.0),
		vec4(-0.359524,2.751434,-0.384325,1.0),
		vec4(0.005286,2.762699,-0.671042,1.0),
		vec4(0.005569,2.814761,-0.508971,1.0),
		vec4(-0.612436,2.762699,0.398883,1.0),
		vec4(-0.545192,2.814761,-0.046827,1.0),
		vec4(-0.478762,2.814761,0.329916,1.0),
		vec4(-0.191317,2.751434,0.569622,1.0),
		vec4(-0.612436,2.762699,0.398883,1.0),
		vec4(-0.478762,2.814761,0.329916,1.0),
		vec4(0.249243,2.762699,0.712509,1.0),
		vec4(-0.191317,2.751434,0.569622,1.0),
		vec4(0.196847,2.814761,0.575818,1.0),
		vec4(0.489901,2.814761,0.329917,1.0),
		vec4(0.249243,2.762699,0.712509,1.0),
		vec4(0.196847,2.814761,0.575818,1.0),
		vec4(0.556331,2.814761,-0.046827,1.0),
		vec4(0.623007,2.762699,0.398883,1.0),
		vec4(0.489901,2.814761,0.329917,1.0),
		vec4(0.365054,2.814761,-0.378129,1.0),
		vec4(0.702124,2.699372,-0.087815,1.0),
		vec4(0.556331,2.814761,-0.046827,1.0),
		vec4(0.005569,2.814761,-0.508971,1.0),
		vec4(0.463775,2.762699,-0.504165,1.0),
		vec4(0.365054,2.814761,-0.378129,1.0),
		vec4(0.001149,2.056518,-0.681816,1.0),
		vec4(0.564756,1.998845,-0.625769,1.0),
		vec4(0.474390,2.056519,-0.509570,1.0),
		vec4(0.474390,2.056519,-0.509570,1.0),
		vec4(0.859436,1.935518,-0.111850,1.0),
		vec4(0.726197,2.056518,-0.073428,1.0),
		vec4(0.726197,2.056518,-0.073428,1.0),
		vec4(0.760756,1.998844,0.485799,1.0),
		vec4(0.638746,2.056519,0.422534,1.0),
		vec4(0.638746,2.056519,0.422534,1.0),
		vec4(0.300687,1.998845,0.871843,1.0),
		vec4(0.252955,2.056519,0.746250,1.0),
		vec4(0.300687,1.998845,0.871843,1.0),
		vec4(-0.256267,1.993192,0.740054,1.0),
		vec4(0.252955,2.056519,0.746250,1.0),
		vec4(-0.256267,1.993192,0.740054,1.0),
		vec4(-0.759959,1.998845,0.485799,1.0),
		vec4(-0.636448,2.056519,0.422534,1.0),
		vec4(-0.759959,1.998845,0.485799,1.0),
		vec4(-0.723899,2.056518,-0.073428,1.0),
		vec4(-0.636448,2.056519,0.422534,1.0),
		vec4(-0.477702,1.993192,-0.515766,1.0),
		vec4(0.000399,1.998844,-0.831178,1.0),
		vec4(0.001149,2.056518,-0.681816,1.0),
		vec4(-0.864248,1.998844,-0.105654,1.0),
		vec4(-0.477702,1.993192,-0.515766,1.0),
		vec4(-0.723899,2.056518,-0.073428,1.0),
		vec4(-1.034949,1.407059,-0.131548,1.0),
		vec4(-0.569643,1.403287,-0.618026,1.0),
		vec4(-0.862932,1.466613,-0.094124,1.0),
		vec4(-0.569643,1.403287,-0.618026,1.0),
		vec4(-0.003388,1.407059,-0.997131,1.0),
		vec4(-0.002290,1.466613,-0.816288,1.0),
		vec4(-0.910528,1.407060,0.574081,1.0),
		vec4(-0.862932,1.466613,-0.094124,1.0),
		vec4(-0.759126,1.466613,0.494589,1.0),
		vec4(-0.306797,1.403287,0.872648,1.0),
		vec4(-0.910528,1.407060,0.574081,1.0),
		vec4(-0.759126,1.466613,0.494589,1.0),
		vec4(0.354870,1.407060,1.034648,1.0),
		vec4(-0.306797,1.403287,0.872648,1.0),
		vec4(0.296607,1.466613,0.878845,1.0),
		vec4(0.754545,1.466613,0.494589,1.0),
		vec4(0.354870,1.407060,1.034648,1.0),
		vec4(0.296607,1.466613,0.878845,1.0),
		vec4(0.858351,1.466613,-0.094124,1.0),
		vec4(0.903752,1.407060,0.574081,1.0),
		vec4(0.754545,1.466613,0.494589,1.0),
		vec4(0.559453,1.466613,-0.611830,1.0),
		vec4(1.022565,1.343733,-0.137744,1.0),
		vec4(0.858351,1.466613,-0.094124,1.0),
		vec4(-0.002290,1.466613,-0.816288,1.0),
		vec4(0.669916,1.407060,-0.752068,1.0),
		vec4(0.559453,1.466613,-0.611830,1.0),
		vec4(-0.005440,1.110557,-0.939428,1.0),
		vec4(0.747414,0.865147,-0.845319,1.0),
		vec4(0.637348,1.110557,-0.705472,1.0),
		vec4(0.747414,0.865147,-0.845319,1.0),
		vec4(0.979368,0.916480,-0.113076,1.0),
		vec4(0.637348,1.110557,-0.705472,1.0),
		vec4(0.979368,0.916480,-0.113076,1.0),
		vec4(1.009368,0.865147,0.640300,1.0),
		vec4(0.860586,0.916480,0.560572,1.0),
		vec4(0.860586,0.916480,0.560572,1.0),
		vec4(0.394483,0.865147,1.156250,1.0),
		vec4(0.336580,1.110557,1.000265,1.0),
		vec4(0.394483,0.865147,1.156250,1.0),
		vec4(-0.353069,1.047231,0.994068,1.0),
		vec4(0.336580,1.110557,1.000265,1.0),
		vec4(-0.413802,0.801821,1.150053,1.0),
		vec4(-0.871465,0.916480,0.560572,1.0),
		vec4(-0.353069,1.047231,0.994068,1.0),
		vec4(-1.023078,0.865147,0.640299,1.0),
		vec4(-0.990247,0.916480,-0.113076,1.0),
		vec4(-0.871465,0.916480,0.560572,1.0),
		vec4(-0.653837,0.853153,-0.711668,1.0),
		vec4(-0.006855,0.865147,-1.119851,1.0),
		vec4(-0.005440,1.110557,-0.939428,1.0),
		vec4(-1.162461,0.865147,-0.150182,1.0),
		vec4(-0.653837,0.853153,-0.711668,1.0),
		vec4(-0.990247,0.916480,-0.113076,1.0),
		vec4(0.019167,5.147034,0.022685,1.0),
		vec4(0.028745,5.147034,0.026171,1.0),
		vec4(0.199847,4.386368,-0.186952,1.0),
		vec4(0.199847,4.386368,-0.186952,1.0),
		vec4(0.028745,5.147034,0.026171,1.0),
		vec4(0.033842,5.147034,0.034998,1.0),
		vec4(0.033842,5.147034,0.034998,1.0),
		vec4(0.032072,5.147034,0.045036,1.0),
		vec4(0.263809,4.386367,0.175798,1.0),
		vec4(0.032072,5.147034,0.045036,1.0),
		vec4(0.024263,5.147034,0.051588,1.0),
		vec4(0.113670,4.386367,0.301780,1.0),
		vec4(0.113670,4.386367,0.301780,1.0),
		vec4(0.024263,5.147034,0.051588,1.0),
		vec4(0.014070,5.147034,0.051588,1.0),
		vec4(0.014070,5.147034,0.051588,1.0),
		vec4(0.006262,5.147034,0.045036,1.0),
		vec4(-0.232462,4.386367,0.175798,1.0),
		vec4(-0.232462,4.386367,0.175798,1.0),
		vec4(0.006262,5.147034,0.045036,1.0),
		vec4(0.004492,5.147034,0.034998,1.0),
		vec4(0.033842,5.147034,0.034998,1.0),
		vec4(0.028745,5.147034,0.026171,1.0),
		vec4(0.032072,5.147034,0.045036,1.0),
		vec4(0.019167,5.147034,0.022685,1.0),
		vec4(0.009589,5.147034,0.026171,1.0),
		vec4(0.014070,5.147034,0.051588,1.0),
		vec4(0.004492,5.147034,0.034998,1.0),
		vec4(0.006262,5.147034,0.045036,1.0),
		vec4(0.014070,5.147034,0.051588,1.0),
		vec4(0.014070,5.147034,0.051588,1.0),
		vec4(0.024263,5.147034,0.051588,1.0),
		vec4(0.019167,5.147034,0.022685,1.0),
		vec4(0.032072,5.147034,0.045036,1.0),
		vec4(0.028745,5.147034,0.026171,1.0),
		vec4(0.019167,5.147034,0.022685,1.0),
		vec4(0.009589,5.147034,0.026171,1.0),
		vec4(0.004492,5.147034,0.034998,1.0),
		vec4(0.014070,5.147034,0.051588,1.0),
		vec4(0.009589,5.147034,0.026171,1.0),
		vec4(0.019167,5.147034,0.022685,1.0),
		vec4(0.015674,4.386367,-0.253986,1.0),
		vec4(-0.266496,4.386367,-0.017217,1.0),
		vec4(0.004492,5.147034,0.034998,1.0),
		vec4(0.009589,5.147034,0.026171,1.0),
		vec4(-0.653837,0.853153,-0.711668,1.0),
		vec4(-0.005440,1.110557,-0.939428,1.0),
		vec4(-0.990247,0.916480,-0.113076,1.0),
		vec4(0.637348,1.110557,-0.705472,1.0),
		vec4(0.979368,0.916480,-0.113076,1.0),
		vec4(-0.005440,1.110557,-0.939428,1.0),
		vec4(0.860586,0.916480,0.560572,1.0),
		vec4(0.336580,1.110557,1.000265,1.0),
		vec4(-0.353069,1.047231,0.994068,1.0),
		vec4(-0.353069,1.047231,0.994068,1.0),
		vec4(-0.871465,0.916480,0.560572,1.0),
		vec4(-0.990247,0.916480,-0.113076,1.0),
		vec4(-0.990247,0.916480,-0.113076,1.0),
		vec4(-0.005440,1.110557,-0.939428,1.0),
		vec4(-0.353069,1.047231,0.994068,1.0),
		vec4(0.979368,0.916480,-0.113076,1.0),
		vec4(0.860586,0.916480,0.560572,1.0),
		vec4(-0.353069,1.047231,0.994068,1.0),
		vec4(-1.162461,0.865147,-0.150182,1.0),
		vec4(-0.862932,1.466613,-0.094124,1.0),
		vec4(-0.569643,1.403287,-0.618026,1.0),
		vec4(-0.569643,1.403287,-0.618026,1.0),
		vec4(-0.002290,1.466613,-0.816288,1.0),
		vec4(-0.006855,0.865147,-1.119851,1.0),
		vec4(-1.023078,0.865147,0.640299,1.0),
		vec4(-0.759126,1.466613,0.494589,1.0),
		vec4(-0.862932,1.466613,-0.094124,1.0),
		vec4(-0.306797,1.403287,0.872648,1.0),
		vec4(-0.759126,1.466613,0.494589,1.0),
		vec4(-1.023078,0.865147,0.640299,1.0),
		vec4(0.394483,0.865147,1.156250,1.0),
		vec4(0.296607,1.466613,0.878845,1.0),
		vec4(-0.306797,1.403287,0.872648,1.0),
		vec4(1.009368,0.865147,0.640300,1.0),
		vec4(0.754545,1.466613,0.494589,1.0),
		vec4(0.296607,1.466613,0.878845,1.0),
		vec4(0.858351,1.466613,-0.094124,1.0),
		vec4(0.754545,1.466613,0.494589,1.0),
		vec4(1.009368,0.865147,0.640300,1.0),
		vec4(0.747414,0.865147,-0.845319,1.0),
		vec4(0.559453,1.466613,-0.611830,1.0),
		vec4(0.858351,1.466613,-0.094124,1.0),
		vec4(-0.002290,1.466613,-0.816288,1.0),
		vec4(0.559453,1.466613,-0.611830,1.0),
		vec4(0.747414,0.865147,-0.845319,1.0),
		vec4(-0.470645,3.612862,-0.047718,1.0),
		vec4(-0.162981,4.436458,0.010068,1.0),
		vec4(-0.106769,4.373131,-0.103204,1.0),
		vec4(-0.106769,4.373131,-0.103204,1.0),
		vec4(0.015024,4.436458,-0.139296,1.0),
		vec4(0.010725,3.612862,-0.451635,1.0),
		vec4(-0.412585,3.612862,0.281558,1.0),
		vec4(-0.141511,4.436458,0.131830,1.0),
		vec4(-0.162981,4.436458,0.010068,1.0),
		vec4(-0.052405,4.373131,0.205109,1.0),
		vec4(-0.141511,4.436458,0.131830,1.0),
		vec4(-0.412585,3.612862,0.281558,1.0),
		vec4(0.177903,3.612862,0.496478,1.0),
		vec4(0.076845,4.436458,0.211305,1.0),
		vec4(-0.052405,4.373131,0.205109,1.0),
		vec4(0.434034,3.612862,0.281558,1.0),
		vec4(0.171559,4.436458,0.131830,1.0),
		vec4(0.076845,4.436458,0.211305,1.0),
		vec4(0.193029,4.436458,0.010068,1.0),
		vec4(0.171559,4.436458,0.131830,1.0),
		vec4(0.434034,3.612862,0.281558,1.0),
		vec4(0.324917,3.612862,-0.337279,1.0),
		vec4(0.131209,4.436458,-0.097008,1.0),
		vec4(0.193029,4.436458,0.010068,1.0),
		vec4(0.015024,4.436458,-0.139296,1.0),
		vec4(0.131209,4.436458,-0.097008,1.0),
		vec4(0.324917,3.612862,-0.337279,1.0),
		vec4(0.010529,3.665409,-0.315061,1.0),
		vec4(0.242392,3.665409,-0.230669,1.0),
		vec4(0.463775,2.762699,-0.504165,1.0),
		vec4(0.463775,2.762699,-0.504165,1.0),
		vec4(0.242392,3.665409,-0.230669,1.0),
		vec4(0.365764,3.665409,-0.016983,1.0),
		vec4(0.365764,3.665409,-0.016983,1.0),
		vec4(0.322917,3.665409,0.226012,1.0),
		vec4(0.623007,2.762699,0.398883,1.0),
		vec4(0.623007,2.762699,0.398883,1.0),
		vec4(0.322917,3.665409,0.226012,1.0),
		vec4(0.133901,3.665409,0.384616,1.0),
		vec4(0.249243,2.762699,0.712509,1.0),
		vec4(0.133901,3.665409,0.384616,1.0),
		vec4(-0.118452,3.602083,0.378420,1.0),
		vec4(-0.118452,3.602083,0.378420,1.0),
		vec4(-0.301860,3.665409,0.226012,1.0),
		vec4(-0.612436,2.762699,0.398883,1.0),
		vec4(-0.612436,2.762699,0.398883,1.0),
		vec4(-0.301860,3.665409,0.226012,1.0),
		vec4(-0.344706,3.665409,-0.016983,1.0),
		vec4(-0.226943,3.602082,-0.236866,1.0),
		vec4(0.010529,3.665409,-0.315061,1.0),
		vec4(0.005286,2.762699,-0.671042,1.0),
		vec4(-0.697161,2.762699,-0.081619,1.0),
		vec4(-0.344706,3.665409,-0.016983,1.0),
		vec4(-0.226943,3.602082,-0.236866,1.0),
		vec4(-0.864248,1.998844,-0.105654,1.0),
		vec4(-0.545192,2.814761,-0.046827,1.0),
		vec4(-0.359524,2.751434,-0.384325,1.0),
		vec4(-0.359524,2.751434,-0.384325,1.0),
		vec4(0.005569,2.814761,-0.508971,1.0),
		vec4(0.000399,1.998844,-0.831178,1.0),
		vec4(-0.759959,1.998845,0.485799,1.0),
		vec4(-0.478762,2.814761,0.329916,1.0),
		vec4(-0.545192,2.814761,-0.046827,1.0),
		vec4(-0.191317,2.751434,0.569622,1.0),
		vec4(-0.478762,2.814761,0.329916,1.0),
		vec4(-0.759959,1.998845,0.485799,1.0),
		vec4(0.300687,1.998845,0.871843,1.0),
		vec4(0.196847,2.814761,0.575818,1.0),
		vec4(-0.191317,2.751434,0.569622,1.0),
		vec4(0.760756,1.998844,0.485799,1.0),
		vec4(0.489901,2.814761,0.329917,1.0),
		vec4(0.196847,2.814761,0.575818,1.0),
		vec4(0.556331,2.814761,-0.046827,1.0),
		vec4(0.489901,2.814761,0.329917,1.0),
		vec4(0.760756,1.998844,0.485799,1.0),
		vec4(0.564756,1.998845,-0.625769,1.0),
		vec4(0.365054,2.814761,-0.378129,1.0),
		vec4(0.556331,2.814761,-0.046827,1.0),
		vec4(0.005569,2.814761,-0.508971,1.0),
		vec4(0.365054,2.814761,-0.378129,1.0),
		vec4(0.564756,1.998845,-0.625769,1.0),
		vec4(0.001149,2.056518,-0.681816,1.0),
		vec4(0.474390,2.056519,-0.509570,1.0),
		vec4(0.669916,1.407060,-0.752068,1.0),
		vec4(0.669916,1.407060,-0.752068,1.0),
		vec4(0.474390,2.056519,-0.509570,1.0),
		vec4(0.726197,2.056518,-0.073428,1.0),
		vec4(0.726197,2.056518,-0.073428,1.0),
		vec4(0.638746,2.056519,0.422534,1.0),
		vec4(0.903752,1.407060,0.574081,1.0),
		vec4(0.903752,1.407060,0.574081,1.0),
		vec4(0.638746,2.056519,0.422534,1.0),
		vec4(0.252955,2.056519,0.746250,1.0),
		vec4(0.354870,1.407060,1.034648,1.0),
		vec4(0.252955,2.056519,0.746250,1.0),
		vec4(-0.256267,1.993192,0.740054,1.0),
		vec4(-0.256267,1.993192,0.740054,1.0),
		vec4(-0.636448,2.056519,0.422534,1.0),
		vec4(-0.910528,1.407060,0.574081,1.0),
		vec4(-0.910528,1.407060,0.574081,1.0),
		vec4(-0.636448,2.056519,0.422534,1.0),
		vec4(-0.723899,2.056518,-0.073428,1.0),
		vec4(-0.477702,1.993192,-0.515766,1.0),
		vec4(0.001149,2.056518,-0.681816,1.0),
		vec4(-0.003388,1.407059,-0.997131,1.0),
		vec4(-1.034949,1.407059,-0.131548,1.0),
		vec4(-0.723899,2.056518,-0.073428,1.0),
		vec4(-0.477702,1.993192,-0.515766,1.0),
		vec4(-0.266496,4.386367,-0.017217,1.0),
		vec4(-0.174109,4.323041,-0.193148,1.0),
		vec4(-0.106769,4.373131,-0.103204,1.0),
		vec4(-0.106769,4.373131,-0.103204,1.0),
		vec4(-0.174109,4.323041,-0.193148,1.0),
		vec4(0.015674,4.386367,-0.253986,1.0),
		vec4(-0.232462,4.386367,0.175798,1.0),
		vec4(-0.266496,4.386367,-0.017217,1.0),
		vec4(-0.162981,4.436458,0.010068,1.0),
		vec4(-0.052405,4.373131,0.205109,1.0),
		vec4(-0.087932,4.323041,0.295584,1.0),
		vec4(-0.232462,4.386367,0.175798,1.0),
		vec4(0.113670,4.386367,0.301780,1.0),
		vec4(-0.087932,4.323041,0.295584,1.0),
		vec4(-0.052405,4.373131,0.205109,1.0),
		vec4(0.171559,4.436458,0.131830,1.0),
		vec4(0.263809,4.386367,0.175798,1.0),
		vec4(0.113670,4.386367,0.301780,1.0),
		vec4(0.193029,4.436458,0.010068,1.0),
		vec4(0.292234,4.323041,-0.023413,1.0),
		vec4(0.263809,4.386367,0.175798,1.0),
		vec4(0.131209,4.436458,-0.097008,1.0),
		vec4(0.199847,4.386368,-0.186952,1.0),
		vec4(0.292234,4.323041,-0.023413,1.0),
		vec4(0.015024,4.436458,-0.139296,1.0),
		vec4(0.015674,4.386367,-0.253986,1.0),
		vec4(0.199847,4.386368,-0.186952,1.0),
		vec4(0.010529,3.665409,-0.315061,1.0),
		vec4(0.010725,3.612862,-0.451635,1.0),
		vec4(0.324917,3.612862,-0.337279,1.0),
		vec4(0.242392,3.665409,-0.230669,1.0),
		vec4(0.324917,3.612862,-0.337279,1.0),
		vec4(0.486486,3.549535,-0.053915,1.0),
		vec4(0.365764,3.665409,-0.016983,1.0),
		vec4(0.486486,3.549535,-0.053915,1.0),
		vec4(0.434034,3.612862,0.281558,1.0),
		vec4(0.322917,3.665409,0.226012,1.0),
		vec4(0.434034,3.612862,0.281558,1.0),
		vec4(0.177903,3.612862,0.496478,1.0),
		vec4(0.177903,3.612862,0.496478,1.0),
		vec4(-0.162062,3.549536,0.490282,1.0),
		vec4(-0.118452,3.602083,0.378420,1.0),
		vec4(-0.118452,3.602083,0.378420,1.0),
		vec4(-0.162062,3.549536,0.490282,1.0),
		vec4(-0.412585,3.612862,0.281558,1.0),
		vec4(-0.412585,3.612862,0.281558,1.0),
		vec4(-0.470645,3.612862,-0.047718,1.0),
		vec4(-0.344706,3.665409,-0.016983,1.0),
		vec4(-0.226943,3.602082,-0.236866,1.0),
		vec4(-0.309076,3.549535,-0.343475,1.0),
		vec4(0.010725,3.612862,-0.451635,1.0),
		vec4(-0.470645,3.612862,-0.047718,1.0),
		vec4(-0.309076,3.549535,-0.343475,1.0),
		vec4(-0.226943,3.602082,-0.236866,1.0),
		vec4(-0.697161,2.762699,-0.081619,1.0),
		vec4(-0.458813,2.699373,-0.510362,1.0),
		vec4(-0.359524,2.751434,-0.384325,1.0),
		vec4(-0.359524,2.751434,-0.384325,1.0),
		vec4(-0.458813,2.699373,-0.510362,1.0),
		vec4(0.005286,2.762699,-0.671042,1.0),
		vec4(-0.612436,2.762699,0.398883,1.0),
		vec4(-0.697161,2.762699,-0.081619,1.0),
		vec4(-0.545192,2.814761,-0.046827,1.0),
		vec4(-0.191317,2.751434,0.569622,1.0),
		vec4(-0.244281,2.699373,0.706312,1.0),
		vec4(-0.612436,2.762699,0.398883,1.0),
		vec4(0.249243,2.762699,0.712509,1.0),
		vec4(-0.244281,2.699373,0.706312,1.0),
		vec4(-0.191317,2.751434,0.569622,1.0),
		vec4(0.489901,2.814761,0.329917,1.0),
		vec4(0.623007,2.762699,0.398883,1.0),
		vec4(0.249243,2.762699,0.712509,1.0),
		vec4(0.556331,2.814761,-0.046827,1.0),
		vec4(0.702124,2.699372,-0.087815,1.0),
		vec4(0.623007,2.762699,0.398883,1.0),
		vec4(0.365054,2.814761,-0.378129,1.0),
		vec4(0.463775,2.762699,-0.504165,1.0),
		vec4(0.702124,2.699372,-0.087815,1.0),
		vec4(0.005569,2.814761,-0.508971,1.0),
		vec4(0.005286,2.762699,-0.671042,1.0),
		vec4(0.463775,2.762699,-0.504165,1.0),
		vec4(0.001149,2.056518,-0.681816,1.0),
		vec4(0.000399,1.998844,-0.831178,1.0),
		vec4(0.564756,1.998845,-0.625769,1.0),
		vec4(0.474390,2.056519,-0.509570,1.0),
		vec4(0.564756,1.998845,-0.625769,1.0),
		vec4(0.859436,1.935518,-0.111850,1.0),
		vec4(0.726197,2.056518,-0.073428,1.0),
		vec4(0.859436,1.935518,-0.111850,1.0),
		vec4(0.760756,1.998844,0.485799,1.0),
		vec4(0.638746,2.056519,0.422534,1.0),
		vec4(0.760756,1.998844,0.485799,1.0),
		vec4(0.300687,1.998845,0.871843,1.0),
		vec4(0.300687,1.998845,0.871843,1.0),
		vec4(-0.305499,1.935518,0.865646,1.0),
		vec4(-0.256267,1.993192,0.740054,1.0),
		vec4(-0.256267,1.993192,0.740054,1.0),
		vec4(-0.305499,1.935518,0.865646,1.0),
		vec4(-0.759959,1.998845,0.485799,1.0),
		vec4(-0.759959,1.998845,0.485799,1.0),
		vec4(-0.864248,1.998844,-0.105654,1.0),
		vec4(-0.723899,2.056518,-0.073428,1.0),
		vec4(-0.477702,1.993192,-0.515766,1.0),
		vec4(-0.569569,1.935518,-0.631965,1.0),
		vec4(0.000399,1.998844,-0.831178,1.0),
		vec4(-0.864248,1.998844,-0.105654,1.0),
		vec4(-0.569569,1.935518,-0.631965,1.0),
		vec4(-0.477702,1.993192,-0.515766,1.0),
		vec4(-1.034949,1.407059,-0.131548,1.0),
		vec4(-0.682301,1.343733,-0.758265,1.0),
		vec4(-0.569643,1.403287,-0.618026,1.0),
		vec4(-0.569643,1.403287,-0.618026,1.0),
		vec4(-0.682301,1.343733,-0.758265,1.0),
		vec4(-0.003388,1.407059,-0.997131,1.0),
		vec4(-0.910528,1.407060,0.574081,1.0),
		vec4(-1.034949,1.407059,-0.131548,1.0),
		vec4(-0.862932,1.466613,-0.094124,1.0),
		vec4(-0.306797,1.403287,0.872648,1.0),
		vec4(-0.367254,1.343733,1.028452,1.0),
		vec4(-0.910528,1.407060,0.574081,1.0),
		vec4(0.354870,1.407060,1.034648,1.0),
		vec4(-0.367254,1.343733,1.028452,1.0),
		vec4(-0.306797,1.403287,0.872648,1.0),
		vec4(0.754545,1.466613,0.494589,1.0),
		vec4(0.903752,1.407060,0.574081,1.0),
		vec4(0.354870,1.407060,1.034648,1.0),
		vec4(0.858351,1.466613,-0.094124,1.0),
		vec4(1.022565,1.343733,-0.137744,1.0),
		vec4(0.903752,1.407060,0.574081,1.0),
		vec4(0.559453,1.466613,-0.611830,1.0),
		vec4(0.669916,1.407060,-0.752068,1.0),
		vec4(1.022565,1.343733,-0.137744,1.0),
		vec4(-0.002290,1.466613,-0.816288,1.0),
		vec4(-0.003388,1.407059,-0.997131,1.0),
		vec4(0.669916,1.407060,-0.752068,1.0),
		vec4(-0.005440,1.110557,-0.939428,1.0),
		vec4(-0.006855,0.865147,-1.119851,1.0),
		vec4(0.747414,0.865147,-0.845319,1.0),
		vec4(0.747414,0.865147,-0.845319,1.0),
		vec4(1.143143,0.801821,-0.156378,1.0),
		vec4(0.979368,0.916480,-0.113076,1.0),
		vec4(0.979368,0.916480,-0.113076,1.0),
		vec4(1.143143,0.801821,-0.156378,1.0),
		vec4(1.009368,0.865147,0.640300,1.0),
		vec4(0.860586,0.916480,0.560572,1.0),
		vec4(1.009368,0.865147,0.640300,1.0),
		vec4(0.394483,0.865147,1.156250,1.0),
		vec4(0.394483,0.865147,1.156250,1.0),
		vec4(-0.413802,0.801821,1.150053,1.0),
		vec4(-0.353069,1.047231,0.994068,1.0),
		vec4(-0.413802,0.801821,1.150053,1.0),
		vec4(-1.023078,0.865147,0.640299,1.0),
		vec4(-0.871465,0.916480,0.560572,1.0),
		vec4(-1.023078,0.865147,0.640299,1.0),
		vec4(-1.162461,0.865147,-0.150182,1.0),
		vec4(-0.990247,0.916480,-0.113076,1.0),
		vec4(-0.653837,0.853153,-0.711668,1.0),
		vec4(-0.766733,0.801821,-0.851516,1.0),
		vec4(-0.006855,0.865147,-1.119851,1.0),
		vec4(-1.162461,0.865147,-0.150182,1.0),
		vec4(-0.766733,0.801821,-0.851516,1.0),
		vec4(-0.653837,0.853153,-0.711668,1.0)
	};
};

