import os
import re
import util

from templates import helper
import extended_helper

def generate_frontend(template, output, header, apiHeader, namespace, actor, functions, handlesDict):
    print("Generating %s..."%output)
    loc = util.makoWrite(
        template, 
        output,
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title(),
        name = actor,
        header = header,
        apiHeader = apiHeader,
        objects = functions,
        handles = handlesDict)
    return loc
    
def generate_frontend_cmake(template, output, driver_headers, driver_sources, mock_headers, test_sources):
    print("Generating %s..."%output)
    loc = util.makoWrite(
        template, 
        output,
        driver_headers = driver_headers,
        driver_sources = driver_sources,
        driver_mocks = mock_headers,
        driver_tests = test_sources
         )
    return loc

"""
    generates c++ driver frontend classess/ults from the specification documents
"""
def generate_driver_frontend(path, namespace, specs):    
    loc = 0
    
    allObjects = []
    for s in specs:
        allObjects = allObjects + s['objects']
    allFunctionsList = [x for x in allObjects if x['type'] == 'function']
    allHandlesDict = dict((extended_helper.handle_to_actor_name(x), x) for x in allObjects if x['type'] == 'handle')
    functionsByActors = dict()
    for f in allFunctionsList:
        if('class' not in f.keys()):
            print("Skipping %s - no actors defined"%f['name'])
            continue
        if(isinstance(f['class'], (list,))):
            for c in f['class']:
                assert(isinstance(c, (str,)))
                actor = extended_helper.class_to_actor_name(c)
                if(actor == ""):
                    continue
                if(actor not in functionsByActors.keys()):
                    functionsByActors[actor] = []
                functionsByActors[actor].append(f)
        else:
            assert(isinstance(f['class'], (str,)))
            actor = extended_helper.class_to_actor_name(f['class'])
            if(actor == ""):
                continue
            if(actor not in functionsByActors.keys()):
                functionsByActors[actor] = []
            functionsByActors[actor].append(f)
    
    driver_headers = []
    driver_sources = []
    mock_headers = []
    test_sources = []
    for actor in functionsByActors.keys():
        if(actor not in allHandlesDict.keys()):
            print("Skipping generation of %s.h/.cpp - no base handle for this actor"%actor)
            continue
        # find the right spec for this actor
        spec = None
        for s in specs:
            for o in s['objects']:
                if((o['type'] == "function") and ('class' in o.keys()) and (isinstance(o['class'], (str,))) and (actor == extended_helper.class_to_actor_name(o['class']))):
                    spec = s
                    break
            if(spec != None):
                break
                
        uniqueFunctionsDict = dict((f['name'], f) for f in functionsByActors[actor])
        uniqueFunctions = [uniqueFunctionsDict[f] for f in uniqueFunctionsDict.keys()]
            
        filename = "%s.h"%actor
        driver_headers.append(filename)
        loc += generate_frontend(os.path.join("templates", "driver_frontend_classes.h.mako"), 
                        os.path.join(path, filename),
                        spec['header'],
                        spec['name'],
                        namespace,
                        actor,
                        uniqueFunctions,
                        allHandlesDict)
                        
        filename = "%s.cpp"%actor
        driver_sources.append(filename)
        loc += generate_frontend(os.path.join("templates", "driver_frontend_classes.cpp.mako"), 
                        os.path.join(path, filename),
                        spec['header'],
                        spec['name'],
                        namespace,
                        actor,
                        uniqueFunctions,
                        allHandlesDict)
                        
        filename = "mock_%s.h"%actor
        mock_headers.append(filename)
        loc += generate_frontend(os.path.join("templates", "driver_frontend_classes_mocks.h.mako"), 
                        os.path.join(path, filename),
                        spec['header'],
                        spec['name'],
                        namespace,
                        actor,
                        uniqueFunctions,
                        allHandlesDict)
                        
        filename = "test_forwarding_%s.cpp"%actor
        test_sources.append(filename)
        loc += generate_frontend(os.path.join("templates", "driver_frontend_classes_forwarding_tests.cpp.mako"), 
                        os.path.join(path, filename),
                        spec['header'],
                        spec['name'],
                        namespace,
                        actor,
                        uniqueFunctions,
                        allHandlesDict)
                        
    
    generate_frontend_cmake(os.path.join("templates", "driver_frontend.cmake.txt.mako"),
                            os.path.join(path, "CMakeLists.txt"),
                            driver_headers, driver_sources, mock_headers, test_sources)
    files = driver_headers + driver_sources + mock_headers + test_sources
    return loc, files