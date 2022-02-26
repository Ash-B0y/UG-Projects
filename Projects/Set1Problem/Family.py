import RelationShip


class Family(RelationShip.RelationShip):
    family_members = {}

    def __init__(self, name, gender, father=None, mother=None):
        self.__name = name
        self.__gender = gender
        self.__mother = mother
        self.__father = father
        self.__spouse = None
        self.__children = None
        self.__siblings = None
        Family.family_members[name] = self

    def __repr__(self):
        return self.__name

    # defining getters and setters
    def get_name(self):
        return self.__name

    def set_name(self, name):
        self.__name = name
        return self

    def get_gender(self):
        return self.__gender

    def set_gender(self, gender):
        self.__gender = gender
        return self

    def get_spouse(self):
        return self.__spouse

    def set_spouse(self, spouse):
        self.__spouse = spouse
        return self

    def get_mother(self):
        return self.__mother

    def set_mother(self, mother):
        self.__mother = mother
        return self

    def get_father(self):
        return self.__father

    def set_father(self, father):
        self.__father = father
        return self

    def get_children(self):
        return self.__children

    def set_children(self, children):
        if type(children) is list:
            self.__children = children
        else:
            self.__children.append(children)
        return self

    def get_siblings(self):
        return self.__siblings

    def set_siblings(self, siblings):
        if type(siblings) is list:
            self.__siblings = siblings
        else:
            self.__siblings.append(siblings)
        return self

