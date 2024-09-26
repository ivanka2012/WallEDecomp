/*
Microsoft Zouna splits these functions up into separate dimension vector files. There's significant information loss here so unfortunately we can't confirm if this is the same case here.
Float3::Get2OrthoVector(Float3&,Float3&)	__text	0022BF5A	000000BE	0000002C	0000000C	R	.	.	.	.	.	B	.	.
Vec4f::ANormalize(void)	__text	0022C018	000001E0	0000003C	00000004	R	.	.	.	.	.	B	T	.
*/
/*
So as it turns out, all Float3's are somehow have been typedeffed or macroed to Vec3f, but there isn't a single reference to a Vec3f type
However, a lot of indirect references get made to Vec3f and gcc uses the parent type for the symbols (see https://godbolt.org/z/MGd6eM8cr) so it's realistic to assume that Float3 is actually a Vec3f.
*/