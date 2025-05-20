#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <string>
#include <vector>
#include <iostream>

class OrganizationComponent {
protected:
    std::string name;

public:
    OrganizationComponent(const std::string& name) : name(name) {}
    virtual ~OrganizationComponent() {}
    
    std::string getName() const { return name; }
    
    virtual void add(OrganizationComponent* component) = 0;
    
    virtual void remove(OrganizationComponent* component) = 0;
    
    
    virtual bool isComposite() const {
        return false;
    }
    
    virtual void showStructure(int depth = 0) const = 0;
    virtual void showResponsibilities() const = 0;
    
    void printIndent(int depth) const {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
    }
};

class Department : public OrganizationComponent {
private:
    std::string responsibility;

public:
    Department(const std::string& name, const std::string& responsibility): OrganizationComponent(name), responsibility(responsibility) {}
    
    void add(OrganizationComponent* component) override {
    }
    
    // 实现继承的纯虚函数 - 部门作为叶节点不支持移除子组件
    void remove(OrganizationComponent* component) override {
    }

    void showStructure(int depth = 0) const override {
        printIndent(depth);
        std::cout << "- " << getName() << std::endl;
    }
    
    void showResponsibilities() const override{
        std::cout << "  * " << getName() << ": " << responsibility << std::endl;
    }
    
    std::string getResponsibility() const { return responsibility; }
};

class OrganizationalEntity : public OrganizationComponent {
private:
    std::vector<Department*> departments;
    std::vector<OrganizationComponent*> subEntities;

public:
    OrganizationalEntity(const std::string& name) : OrganizationComponent(name) {}
    
    ~OrganizationalEntity() {
        // 释放部门内存
        for (auto* dept : departments) {
            delete dept;
        }
        
        // 释放子实体内存
        for (auto* entity : subEntities) {
            delete entity;
        }
    }
    
    // 添加部门
    void addDepartment(const std::string& name, const std::string& responsibility) {
        departments.push_back(new Department(name, responsibility));
    }
    
    // 添加子实体
    void add(OrganizationComponent* component) override {
        subEntities.push_back(component);
    }
    
    // 移除子实体
    void remove(OrganizationComponent* component) override {
        for (auto it = subEntities.begin(); it != subEntities.end(); ++it) {
            if (*it == component) {
                subEntities.erase(it);
                return;
            }
        }
    }
    
    bool isComposite() const override {
        return true;
    }
    
    // 显示组织结构
    void showStructure(int depth = 0) const override {
        // 显示当前实体
        printIndent(depth);
        std::cout << "+ " << getName() << std::endl;
        
        // 显示所有部门
        for (const auto* dept : departments) {
            dept->showStructure(depth + 1);
        }
        
        // 递归显示子实体
        for (const auto* entity : subEntities) {
            entity->showStructure(depth + 1);
        }
    }
    
    // 显示职责
    void showResponsibilities() const override {
        std::cout << "实体: " << getName() << " 的职责:" << std::endl;
        
        // 显示当前实体的部门职责
        for (const auto* dept : departments) {
            dept->showResponsibilities();
        }
        
        std::cout << std::endl;
        
        // 递归显示子实体的职责
        for (const auto* entity : subEntities) {
            entity->showResponsibilities();
        }
    }
};

#endif // ORGANIZATION_H