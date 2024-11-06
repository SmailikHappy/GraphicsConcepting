struct FCustomVertex
{
public:
	FVector3f Position;
	FVector2f UV;
};

struct SVertexPassInfo
{
public:
	int BaseVertexIndex = 0;
	int MinIndex = 0;
	int NumVertices = 0;
	int StartIndex = 0;
	int NumPrimitives = 0;
	int NumInstances = 0;
};

class FCustomSquareVertexBuffer : public FVertexBuffer
{
public:
	/** Initialize the RHI for this rendering resource */
	void InitRHI(FRHICommandListBase& RHICmdList) override {
		TResourceArray<FCustomVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
		Vertices.SetNumUninitialized(4);
		Vertices[0].Position = FVector3f(-1.0f,  1.0f, 0.0f);
		Vertices[0].UV		 = FVector2f(0.0f, 1.0f);
		Vertices[1].Position = FVector3f(-1.0f, -1.0f, 0.0f);
		Vertices[1].UV		 = FVector2f(0.0f, 0.0f);
		Vertices[2].Position = FVector3f( 1.0f,  1.0f, 0.0f);
		Vertices[2].UV		 = FVector2f(1.0f, 1.0f);
		Vertices[3].Position = FVector3f( 1.0f, -1.0f, 0.0f);
		Vertices[3].UV		 = FVector2f(0.0f, 0.0f);
		FRHIResourceCreateInfo CreateInfo(TEXT("FScreenCustomTrangleVertexBuffer"), &Vertices);
		VertexBufferRHI = RHICmdList.CreateVertexBuffer(Vertices.GetResourceDataSize(), BUF_Static, CreateInfo);
	}
};

class FCustomSquareIndexBuffer : public FIndexBuffer
{
public:
	/** Initialize the RHI for this rendering resource */
	void InitRHI(FRHICommandListBase& RHICmdList) override
	{
		const uint16 Indices[] = {
			0, 1, 2,
			1, 2, 3
		};
		TResourceArray<uint16, INDEXBUFFER_ALIGNMENT> IndexBuffer;
		uint32 NumIndices = UE_ARRAY_COUNT(Indices);
		IndexBuffer.AddUninitialized(NumIndices);
		FMemory::Memcpy(IndexBuffer.GetData(), Indices, NumIndices * sizeof(uint16));
		FRHIResourceCreateInfo CreateInfo(TEXT("FCustomTrangleIndexBuffer"), &IndexBuffer);
		IndexBufferRHI = RHICmdList.CreateIndexBuffer(sizeof(uint16), IndexBuffer.GetResourceDataSize(), BUF_Static, CreateInfo);
	}
};


class FCustomSquareVertexDeclaration : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;
	/** Destructor. */
	virtual ~FCustomSquareVertexDeclaration() {}
	virtual void InitRHI(FRHICommandListBase& RHICmdList)
	{
		FVertexDeclarationElementList Elements;
		uint16 Stride = sizeof(FCustomVertex);
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FCustomVertex, Position), VET_Float3, 0, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FCustomVertex, UV), VET_Float2, 1, Stride));
		VertexDeclarationRHI = PipelineStateCache::GetOrCreateVertexDeclaration(Elements);
	}
	virtual void ReleaseRHI()
	{
		VertexDeclarationRHI.SafeRelease();
	}
};