#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <map>

template<typename T>
class BaseEntity {
public:
    static unsigned int generateId(const std::map<unsigned int, T*>& entityMap) {
        if (entityMap.empty()) {
            return 1; 
        }
        return entityMap.rbegin()->first + 1; 
    }
    
    bool add(const T& entity) {
        T* pEntity = new T(entity);
        auto result = entityMap.insert(std::make_pair(entity.getId(), pEntity));
        if (!result.second) {  // Ű �ߺ��� ���
            delete pEntity;
            return false;
        }
        appendToFile(entity);  // ���Ͽ� �߰�
        return true;
    }

    
    bool remove(unsigned int id) {
        auto it = entityMap.find(id);
        if (it == entityMap.end()) {  // �ش� ID�� ��ƼƼ�� ���� ���
            return false;
        }
        delete it->second;  // �޸� ����
        entityMap.erase(it);  // �ʿ��� ��ƼƼ ����
        removeFromFile(id);  // ���Ͽ��� ��ƼƼ ����
        return true;
    }

protected:
    virtual void appendToFile(const T& entity) const = 0;  // ���Ͽ� �߰� (���� ���� �Լ�)
    virtual void removeFromFile(unsigned int id) const = 0;  // ���Ͽ��� ���� (���� ���� �Լ�)
};

#endif // BASEENTITY_H
