#include <iostream>
#include "Organization.h"

int main() {
    // 创建微软总部
    OrganizationalEntity* microsoftHQ = new OrganizationalEntity("Microsoft Corporation (总部)");
    microsoftHQ->addDepartment("人力资源部", "负责全球人才招聘与管理");
    microsoftHQ->addDepartment("财务部", "负责全球财务规划与管理");
    microsoftHQ->addDepartment("研发部", "负责前沿技术研究与开发");
    microsoftHQ->addDepartment("销售部", "负责全球销售策略制定与业务拓展");  // 添加总部销售部
    
    // 创建北美分公司
    OrganizationalEntity* northAmerica = new OrganizationalEntity("Microsoft North America");
    northAmerica->addDepartment("人力资源部", "负责北美区域人员管理");
    northAmerica->addDepartment("财务部", "负责北美区域财务管理");
    northAmerica->addDepartment("销售部", "负责北美地区市场开发与客户关系");  // 添加北美销售部
    
    // 创建美国子公司
    OrganizationalEntity* microsoftUS = new OrganizationalEntity("Microsoft US");
    microsoftUS->addDepartment("人力资源部", "负责美国员工管理");
    microsoftUS->addDepartment("财务部", "负责美国财务运营");
    microsoftUS->addDepartment("销售部", "负责美国市场销售渠道建设");  // 添加美国销售部
    
    // 创建雷德蒙德总部办事处
    OrganizationalEntity* redmondOffice = new OrganizationalEntity("Redmond Office");
    redmondOffice->addDepartment("人力资源部", "负责总部员工管理");
    redmondOffice->addDepartment("Windows部门", "负责Windows系统研发");
    redmondOffice->addDepartment("销售部", "负责西雅图地区客户维护与服务");  // 添加雷德蒙德销售部
    
    // 创建亚太分公司
    OrganizationalEntity* asiaPacificBranch = new OrganizationalEntity("Microsoft Asia Pacific");
    asiaPacificBranch->addDepartment("人力资源部", "负责亚太区域人员管理");
    asiaPacificBranch->addDepartment("财务部", "负责亚太区域财务管理");
    asiaPacificBranch->addDepartment("销售部", "负责亚太区域市场开发与销售");  // 添加亚太销售部
    
    // 创建中国子公司
    OrganizationalEntity* chinaSubCompany = new OrganizationalEntity("Microsoft China");
    chinaSubCompany->addDepartment("人力资源部", "负责中国员工管理");
    chinaSubCompany->addDepartment("研发部", "负责中国研发中心工作");
    chinaSubCompany->addDepartment("销售部", "负责中国市场产品销售与推广");  // 添加中国销售部
    
    // 创建北京办事处
    OrganizationalEntity* beijingOffice = new OrganizationalEntity("Beijing Office");
    beijingOffice->addDepartment("人力资源部", "负责北京员工管理");
    beijingOffice->addDepartment("亚洲研究院", "负责亚洲基础研究项目");
    beijingOffice->addDepartment("销售部", "负责华北区客户开发与维护");  // 添加北京销售部
    
    // 建立组织结构
    microsoftUS->add(redmondOffice);
    northAmerica->add(microsoftUS);
    
    chinaSubCompany->add(beijingOffice);
    asiaPacificBranch->add(chinaSubCompany);
    
    microsoftHQ->add(northAmerica);
    microsoftHQ->add(asiaPacificBranch);
    
    // 展示组织结构
    std::cout << "===================== 微软公司组织结构 =====================" << std::endl;
    microsoftHQ->showStructure();
    std::cout << std::endl;
    
    // 展示实体职责
    std::cout << "===================== 微软公司实体职责 =====================" << std::endl;
    microsoftHQ->showResponsibilities();
    
    // 释放内存 - 由于使用组合模式，只需释放根节点
    delete microsoftHQ;
    
    system("pause");
    
    return 0;
}