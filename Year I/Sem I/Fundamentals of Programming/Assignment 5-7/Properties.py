def returnValue(string):
    return string.split()[2]

def interpretProperties():
    with open("settings.properties") as properties:
        line = properties.readline()
        repositoryMode = returnValue(line)
        
        line = properties.readline()
        students = returnValue(line)
        
        line = properties.readline()
        disciplines = returnValue(line)
        
        line = properties.readline()
        grades = returnValue(line)
        
        return [repositoryMode, students, disciplines, grades]