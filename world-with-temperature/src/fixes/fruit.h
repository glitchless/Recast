//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_FIXES_H
#define RECAST_FIXES_H


/**
 * Original macro is INJECT(Signature). It's defined in `<fruit/macro.h>`.
 */
#define INJECT_F(Signature) \
using Inject = Signature; \
protected: \
template <typename FruitAssistedDeclarationParam> \
using FruitAssistedTypedef = FruitAssistedDeclarationParam; \
template <typename Annotation, typename FruitAnnotatedDeclarationParam> \
using FruitAnnotatedTypedef = FruitAnnotatedDeclarationParam; \
public: \
Signature


#endif //RECAST_FIXES_H
