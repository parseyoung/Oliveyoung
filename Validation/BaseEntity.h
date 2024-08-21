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
        if (!result.second) {  // 키 중복인 경우
            delete pEntity;
            return false;
        }
        appendToFile(entity);  // 파일에 추가
        return true;
    }

    
    bool remove(unsigned int id) {
        auto it = entityMap.find(id);
        if (it == entityMap.end()) {  // 해당 ID의 엔티티가 없는 경우
            return false;
        }
        delete it->second;  // 메모리 해제
        entityMap.erase(it);  // 맵에서 엔티티 제거
        removeFromFile(id);  // 파일에서 엔티티 제거
        return true;
    }

protected:
    virtual void appendToFile(const T& entity) const = 0;  // 파일에 추가 (순수 가상 함수)
    virtual void removeFromFile(unsigned int id) const = 0;  // 파일에서 제거 (순수 가상 함수)
};

#endif // BASEENTITY_H
