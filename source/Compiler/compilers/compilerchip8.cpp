#include "compilerchip8.h"


CompilerChip8::CompilerChip8(QSharedPointer<CIniFile> ini, QSharedPointer<CIniFile> pIni) : Compiler(ini, pIni) {

}

void CompilerChip8::InitAssemblerAnddispatcher(QSharedPointer<AbstractSystem> system)
{
    m_assembler = QSharedPointer<AsmChip8>(new AsmChip8());//
    m_codeGen = QSharedPointer<CodeGenChip8>(new CodeGenChip8());
    m_codeGen->dontOutputLineNumbers();
    m_assembler->m_symTab->m_constants = m_parser.m_symTab->m_constants;
    // Init default stuff
    QString blk0=m_assembler->NewLabel("block0");
    m_assembler->Asm("jp "+blk0);
    m_assembler->IncludeFile(":resources/code/chip8/init.asm");
    m_assembler->Label(blk0);

}

void CompilerChip8::Connect()
{
    m_assembler->m_source<<m_parser.m_parserAppendix;
    m_assembler->Connect();
    m_assembler->EndMemoryBlock();
    for (QString&s :m_assembler->m_source) {
        s = s.replace("$","#");
    }

}

bool CompilerChip8::SetupMemoryAnalyzer(QString filename, Orgasm *orgAsm)
{
    return true;
}
