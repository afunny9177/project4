// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HACK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HACK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HACK_EXPORTS
#define HACK_API __declspec(dllexport)
#else
#define HACK_API __declspec(dllimport)
#endif

// �����Ǵ� hack.dll ������
class HACK_API Chack {
public:
	Chack(void);
	// TODO:  �ڴ�������ķ�����
};

extern HACK_API int nhack;

HACK_API int fnhack(void);
